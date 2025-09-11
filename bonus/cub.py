import sys
import random
from typing import List, Tuple, Set

class CubToRtConverter:
    def __init__(self, optimize=True):
        self.triangles = []
        self.optimize = optimize
        self.parsed_data = {
            'ambient': None,
            'camera': None,
            'light': None,
            'map': []
        }
    
    def parse_cub_file(self, filename: str):
        """Parse le fichier .cub et extrait les informations"""
        try:
            with open(filename, 'r') as file:
                lines = file.readlines()
        except FileNotFoundError:
            print(f"Erreur: Le fichier {filename} n'a pas été trouvé.")
            return False
        
        for line in lines:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            
            parts = line.split()
            if not parts:
                continue
            
            # Parse les éléments de configuration
            if parts[0] == 'A':
                self.parsed_data['ambient'] = {
                    'ratio': float(parts[1]),
                    'color': list(map(int, parts[2].split(',')))
                }
            elif parts[0] == 'C':
                self.parsed_data['camera'] = {
                    'position': list(map(float, parts[1].split(','))),
                    'direction': list(map(float, parts[2].split(','))),
                    'fov': int(parts[3])
                }
            elif parts[0] == 'L':
                self.parsed_data['light'] = {
                    'position': list(map(float, parts[1].split(','))),
                    'brightness': float(parts[2]),
                    'color': list(map(int, parts[3].split(',')))
                }
            else:
                # C'est probablement une ligne de la carte
                if all(c in '01NSEW ' for c in line):
                    self.parsed_data['map'].append(line)
        
        return True
    
    def generate_random_color(self) -> Tuple[int, int, int]:
        """Génère une couleur aléatoire"""
        return (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
    
    def create_wall_faces_simple(self, wall_positions: Set[Tuple[int, int]]):
        """Version simple : une face par direction pour chaque mur (sans optimisation)"""
        for x, z in wall_positions:
            wall_height = 1.0
            
            # Face Nord (vers z négatif)
            if (x, z-1) not in wall_positions:
                color = self.generate_random_color()
                # Rectangle de (x,0,z) à (x+1,wall_height,z)
                p1 = (x, 0, z)
                p2 = (x+1, 0, z)
                p3 = (x+1, wall_height, z)
                p4 = (x, wall_height, z)
                
                self.triangles.append({'p1': p1, 'p2': p2, 'p3': p3, 'color': color})
                self.triangles.append({'p1': p1, 'p2': p3, 'p3': p4, 'color': color})
            
            # Face Sud (vers z positif)
            if (x, z+1) not in wall_positions:
                color = self.generate_random_color()
                # Rectangle de (x,0,z+1) à (x+1,wall_height,z+1)
                p1 = (x, 0, z+1)
                p2 = (x+1, 0, z+1)
                p3 = (x+1, wall_height, z+1)
                p4 = (x, wall_height, z+1)
                
                self.triangles.append({'p1': p2, 'p2': p1, 'p3': p4, 'color': color})
                self.triangles.append({'p1': p2, 'p2': p4, 'p3': p3, 'color': color})
            
            # Face Ouest (vers x négatif)
            if (x-1, z) not in wall_positions:
                color = self.generate_random_color()
                # Rectangle de (x,0,z) à (x,wall_height,z+1)
                p1 = (x, 0, z)
                p2 = (x, 0, z+1)
                p3 = (x, wall_height, z+1)
                p4 = (x, wall_height, z)
                
                self.triangles.append({'p1': p1, 'p2': p2, 'p3': p3, 'color': color})
                self.triangles.append({'p1': p1, 'p2': p3, 'p3': p4, 'color': color})
            
            # Face Est (vers x positif)
            if (x+1, z) not in wall_positions:
                color = self.generate_random_color()
                # Rectangle de (x+1,0,z) à (x+1,wall_height,z+1)
                p1 = (x+1, 0, z)
                p2 = (x+1, 0, z+1)
                p3 = (x+1, wall_height, z+1)
                p4 = (x+1, wall_height, z)
                
                self.triangles.append({'p1': p2, 'p2': p1, 'p3': p4, 'color': color})
                self.triangles.append({'p1': p2, 'p2': p4, 'p3': p3, 'color': color})
    
    def create_wall_faces_optimized(self, wall_positions: Set[Tuple[int, int]]):
        """Version optimisée : groupe les faces contigues"""
        processed_faces = set()
        
        # Pour chaque direction, trouver les segments contigus
        directions = [
            ('north', (0, -1)),  # Face nord
            ('south', (0, 1)),   # Face sud  
            ('west', (-1, 0)),   # Face ouest
            ('east', (1, 0))     # Face est
        ]
        
        for direction_name, (dx, dz) in directions:
            # Trouver toutes les positions qui ont besoin d'une face dans cette direction
            face_positions = []
            for x, z in wall_positions:
                neighbor_pos = (x + dx, z + dz)
                if neighbor_pos not in wall_positions:
                    face_positions.append((x, z))
            
            # Grouper les faces contigues
            visited = set()
            for x, z in face_positions:
                if (x, z, direction_name) in visited:
                    continue
                
                # Trouver le segment continu dans cette direction
                segment = self.find_continuous_segment((x, z), face_positions, direction_name, visited)
                if segment:
                    self.create_optimized_face(segment, direction_name)
    
    def find_continuous_segment(self, start_pos, face_positions, direction, visited):
        """Trouve un segment continu de faces dans une direction donnée"""
        x, z = start_pos
        segment = [(x, z)]
        visited.add((x, z, direction))
        
        if direction in ['north', 'south']:
            # Segment horizontal - étendre en X
            # Vers la droite
            curr_x = x + 1
            while (curr_x, z) in face_positions and (curr_x, z, direction) not in visited:
                segment.append((curr_x, z))
                visited.add((curr_x, z, direction))
                curr_x += 1
            
            # Vers la gauche
            curr_x = x - 1
            while (curr_x, z) in face_positions and (curr_x, z, direction) not in visited:
                segment.insert(0, (curr_x, z))
                visited.add((curr_x, z, direction))
                curr_x -= 1
        
        else:  # west, east
            # Segment vertical - étendre en Z
            # Vers le bas
            curr_z = z + 1
            while (x, curr_z) in face_positions and (x, curr_z, direction) not in visited:
                segment.append((x, curr_z))
                visited.add((x, curr_z, direction))
                curr_z += 1
            
            # Vers le haut
            curr_z = z - 1
            while (x, curr_z) in face_positions and (x, curr_z, direction) not in visited:
                segment.insert(0, (x, curr_z))
                visited.add((x, curr_z, direction))
                curr_z -= 1
        
        return segment
    
    def create_optimized_face(self, segment, direction):
        """Crée une face optimisée pour un segment"""
        if not segment:
            return
        
        color = self.generate_random_color()
        wall_height = 1.0
        
        if direction == 'north':
            # Face horizontale vers le nord
            min_x = min(pos[0] for pos in segment)
            max_x = max(pos[0] for pos in segment)
            z = segment[0][1]  # Tous ont le même Z
            
            p1 = (min_x, 0, z)
            p2 = (max_x + 1, 0, z)
            p3 = (max_x + 1, wall_height, z)
            p4 = (min_x, wall_height, z)
            
        elif direction == 'south':
            # Face horizontale vers le sud
            min_x = min(pos[0] for pos in segment)
            max_x = max(pos[0] for pos in segment)
            z = segment[0][1] + 1  # Tous ont le même Z
            
            p1 = (min_x, 0, z)
            p2 = (max_x + 1, 0, z)
            p3 = (max_x + 1, wall_height, z)
            p4 = (min_x, wall_height, z)
            
        elif direction == 'west':
            # Face verticale vers l'ouest
            x = segment[0][0]  # Tous ont le même X
            min_z = min(pos[1] for pos in segment)
            max_z = max(pos[1] for pos in segment)
            
            p1 = (x, 0, min_z)
            p2 = (x, 0, max_z + 1)
            p3 = (x, wall_height, max_z + 1)
            p4 = (x, wall_height, min_z)
            
        else:  # east
            # Face verticale vers l'est
            x = segment[0][0] + 1  # Tous ont le même X
            min_z = min(pos[1] for pos in segment)
            max_z = max(pos[1] for pos in segment)
            
            p1 = (x, 0, min_z)
            p2 = (x, 0, max_z + 1)
            p3 = (x, wall_height, max_z + 1)
            p4 = (x, wall_height, min_z)
        
        # Créer les 2 triangles
        self.triangles.append({'p1': p1, 'p2': p2, 'p3': p3, 'color': color})
        self.triangles.append({'p1': p1, 'p2': p3, 'p3': p4, 'color': color})
    
    def process_map(self):
        """Traite la carte et génère les triangles pour les murs"""
        if not self.parsed_data['map']:
            print("Erreur: Aucune carte trouvée dans le fichier .cub")
            return
        
        # Trouver toutes les positions des murs
        wall_positions = set()
        for row_idx, row in enumerate(self.parsed_data['map']):
            for col_idx, cell in enumerate(row):
                if cell == '1':
                    wall_positions.add((col_idx, row_idx))
        
        print(f"Nombre total de murs: {len(wall_positions)}")
        
        # Choisir l'algorithme
        if self.optimize:
            print("Utilisation de l'algorithme optimisé")
            self.create_wall_faces_optimized(wall_positions)
        else:
            print("Utilisation de l'algorithme simple")
            self.create_wall_faces_simple(wall_positions)
        
        print(f"Nombre total de triangles générés: {len(self.triangles)}")
    
    def generate_rt_file(self, output_filename: str):
        """Génère le fichier .rt"""
        try:
            with open(output_filename, 'w') as file:
                # Écrire l'ambient
                if self.parsed_data['ambient']:
                    a = self.parsed_data['ambient']
                    file.write(f"A\t\t{a['ratio']}\t\t {a['color'][0]},{a['color'][1]},{a['color'][2]}\n")
                
                # Écrire la caméra
                if self.parsed_data['camera']:
                    c = self.parsed_data['camera']
                    pos_str = f"{c['position'][0]},{c['position'][1]},{c['position'][2]}"
                    dir_str = f"{c['direction'][0]},{c['direction'][1]},{c['direction'][2]}"
                    file.write(f"C\t\t{pos_str}\t{dir_str}\t\t\t\t\t{c['fov']}\n")
                
                # Écrire la lumière
                if self.parsed_data['light']:
                    l = self.parsed_data['light']
                    pos_str = f"{l['position'][0]},{l['position'][1]},{l['position'][2]}"
                    col_str = f"{l['color'][0]},{l['color'][1]},{l['color'][2]}"
                    file.write(f"L\t\t{pos_str}\t\t{l['brightness']}\t\t\t\t\t{col_str}\n")
                
                # Ajouter un plan (sol)
                file.write("pl\t\t0,-1,0\t\t0,1,0\t\t\t\t\t0,0,0   1   1   1   255,255,255   0\n")
                
                # Écrire tous les triangles
                for triangle in self.triangles:
                    p1 = triangle['p1']
                    p2 = triangle['p2']
                    p3 = triangle['p3']
                    color = triangle['color']
                    
                    p1_str = f"{p1[0]},{p1[1]},{p1[2]}"
                    p2_str = f"{p2[0]},{p2[1]},{p2[2]}"
                    p3_str = f"{p3[0]},{p3[1]},{p3[2]}"
                    col_str = f"{color[0]},{color[1]},{color[2]}"
                    
                    file.write(f"tr\t\t{p1_str}\t\t{p2_str}\t{p3_str}\t\t{col_str}\t0\n")
        
        except Exception as e:
            print(f"Erreur lors de l'écriture du fichier {output_filename}: {e}")
            return False
        
        return True
    
    def convert(self, input_filename: str, output_filename: str):
        """Fonction principale de conversion"""
        print(f"Conversion de {input_filename} vers {output_filename}")
        
        if not self.parse_cub_file(input_filename):
            return False
        
        self.process_map()
        
        if not self.generate_rt_file(output_filename):
            return False
        
        print(f"Conversion terminée avec succès!")
        print(f"Fichier {output_filename} généré avec {len(self.triangles)} triangles.")
        return True

def main():
    if len(sys.argv) < 3:
        print("Usage: python cub_to_rt.py <fichier.cub> <fichier.rt> [--simple]")
        print("  --simple : utilise l'algorithme simple (plus de triangles mais sans bug)")
        print("Exemple: python cub_to_rt.py map.cub map.rt")
        return
    
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    optimize = '--simple' not in sys.argv
    
    if not input_file.endswith('.cub'):
        print("Erreur: Le fichier d'entrée doit avoir l'extension .cub")
        return
    
    if not output_file.endswith('.rt'):
        print("Erreur: Le fichier de sortie doit avoir l'extension .rt")
        return
    
    converter = CubToRtConverter(optimize=optimize)
    converter.convert(input_file, output_file)

if __name__ == "__main__":
    main()
