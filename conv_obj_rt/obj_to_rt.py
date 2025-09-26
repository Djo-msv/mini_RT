#!/usr/bin/env python3
"""
Convertisseur de fichiers .obj vers .rt
Transforme les triangles d'un modèle 3D OBJ en format RT
"""

import sys
import os
from PIL import Image
import numpy as np
from collections import Counter

def extract_dominant_color(image_path, method='average'):
    """Extrait la couleur dominante d'une image texture"""
    try:
        img = Image.open(image_path)
        img = img.convert('RGB')
        
        if method == 'average':
            # Méthode 1: Couleur moyenne
            np_img = np.array(img)
            avg_color = np.mean(np_img, axis=(0, 1))
            return tuple(map(int, avg_color))
        
        elif method == 'dominant':
            # Méthode 2: Couleur la plus fréquente
            img = img.resize((50, 50))  # Réduction pour performance
            pixels = list(img.getdata())
            most_common = Counter(pixels).most_common(1)[0][0]
            return most_common
            
        elif method == 'median':
            # Méthode 3: Couleur médiane
            np_img = np.array(img)
            median_color = np.median(np_img, axis=(0, 1))
            return tuple(map(int, median_color))
            
    except Exception as e:
        print(f"Erreur lors de la lecture de la texture {image_path}: {e}")
        return None

def parse_mtl_file(mtl_path):
    """Parse un fichier .mtl pour extraire les textures et couleurs"""
    materials = {}
    current_material = None
    
    try:
        with open(mtl_path, 'r') as file:
            for line in file:
                line = line.strip()
                if not line or line.startswith('#'):
                    continue
                    
                parts = line.split()
                if not parts:
                    continue
                
                # Nouveau matériau
                if parts[0] == 'newmtl':
                    current_material = parts[1]
                    materials[current_material] = {}
                
                elif current_material:
                    # Couleur diffuse
                    if parts[0] == 'Kd' and len(parts) >= 4:
                        r, g, b = float(parts[1]), float(parts[2]), float(parts[3])
                        materials[current_material]['color'] = (int(r*255), int(g*255), int(b*255))
                    
                    # Texture diffuse
                    elif parts[0] == 'map_Kd' and len(parts) >= 2:
                        materials[current_material]['texture'] = parts[1]
                        
    except FileNotFoundError:
        print(f"Fichier .mtl non trouvé : {mtl_path}")
    except Exception as e:
        print(f"Erreur lors de la lecture du fichier .mtl : {e}")
    
    return materials
def parse_obj_file(filepath):
    """Parse un fichier .obj et extrait les vertices, faces, coordonnées UV et matériaux"""
    vertices = []
    texture_coords = []  # Coordonnées UV
    faces = []
    materials = {}
    current_material = None
    mtl_file = None
    
    try:
        base_dir = os.path.dirname(filepath)
        
        with open(filepath, 'r') as file:
            for line in file:
                line = line.strip()
                if not line or line.startswith('#'):
                    continue
                
                parts = line.split()
                if not parts:
                    continue
                    
                # Parse vertices (v x y z)
                if parts[0] == 'v':
                    if len(parts) >= 4:
                        x, y, z = float(parts[1]), float(parts[2]), float(parts[3])
                        vertices.append((x, y, z))
                
                # Parse coordonnées de texture (vt u v)
                elif parts[0] == 'vt':
                    if len(parts) >= 3:
                        u, v = float(parts[1]), float(parts[2])
                        texture_coords.append((u, v))
                
                # Référence au fichier matériau
                elif parts[0] == 'mtllib':
                    mtl_file = os.path.join(base_dir, parts[1])
                    materials = parse_mtl_file(mtl_file)
                
                # Utilisation d'un matériau
                elif parts[0] == 'usemtl':
                    current_material = parts[1]
                
                # Parse faces avec coordonnées UV
                elif parts[0] == 'f':
                    if len(parts) >= 4:
                        # Extraction des indices (vertex/texture/normal)
                        face_vertices = []
                        face_uvs = []
                        
                        for i in range(1, len(parts)):
                            vertex_data = parts[i].split('/')
                            
                            # Index du vertex (obligatoire)
                            vertex_index = int(vertex_data[0]) - 1
                            face_vertices.append(vertex_index)
                            
                            # Index des coordonnées UV (optionnel)
                            if len(vertex_data) > 1 and vertex_data[1]:
                                uv_index = int(vertex_data[1]) - 1
                                face_uvs.append(uv_index)
                            else:
                                face_uvs.append(None)
                        
                        # Triangulation robuste pour faces non-triangulaires
                        triangulated_faces = robust_triangulation_with_uv(face_vertices, face_uvs)
                        
                        for triangle_data in triangulated_faces:
                            faces.append((triangle_data, current_material))
    
    except FileNotFoundError:
        print(f"Erreur : Le fichier {filepath} n'existe pas.")
        return None, None, None, None
    except Exception as e:
        print(f"Erreur lors de la lecture du fichier : {e}")
        return None, None, None, None
    
    return vertices, texture_coords, faces, materials

def robust_triangulation_with_uv(face_vertices, face_uvs):
    """Triangulation avec préservation des coordonnées UV"""
    if len(face_vertices) < 3:
        return []
    
    if len(face_vertices) == 3:
        return [{'vertices': face_vertices, 'uvs': face_uvs}]
    
    triangles = []
    
    # Triangulation en éventail en préservant les UVs
    for i in range(2, len(face_vertices)):
        triangle_vertices = (face_vertices[0], face_vertices[i-1], face_vertices[i])
        triangle_uvs = (face_uvs[0], face_uvs[i-1], face_uvs[i])
        
        triangles.append({
            'vertices': triangle_vertices, 
            'uvs': triangle_uvs
        })
    
    return triangles

def sample_triangle_color(image, uv_coords):
    """Échantillonne la couleur moyenne d'un triangle sur une texture"""
    if not image or not all(uv is not None for uv in uv_coords):
        return None
    
    try:
        img_width, img_height = image.size
        
        # Conversion des coordonnées UV en pixels
        pixel_coords = []
        for u, v in uv_coords:
            # Clamping des coordonnées UV entre 0 et 1
            u = max(0, min(1, u))
            v = max(0, min(1, 1 - v))  # Flip V car les images sont inversées
            
            px = int(u * (img_width - 1))
            py = int(v * (img_height - 1))
            pixel_coords.append((px, py))
        
        # Calcul de la bounding box du triangle
        min_x = max(0, min(coord[0] for coord in pixel_coords))
        max_x = min(img_width - 1, max(coord[0] for coord in pixel_coords))
        min_y = max(0, min(coord[1] for coord in pixel_coords))
        max_y = min(img_height - 1, max(coord[1] for coord in pixel_coords))
        
        # Échantillonnage des pixels dans la bounding box
        sampled_colors = []
        
        for y in range(min_y, max_y + 1):
            for x in range(min_x, max_x + 1):
                # Test simple : est-ce que le point est dans le triangle ?
                if is_point_in_triangle((x, y), pixel_coords):
                    color = image.getpixel((x, y))
                    if isinstance(color, tuple) and len(color) >= 3:
                        sampled_colors.append(color[:3])
        
        # Si pas assez d'échantillons, échantillonner aux sommets
        if len(sampled_colors) < 3:
            for px, py in pixel_coords:
                color = image.getpixel((px, py))
                if isinstance(color, tuple) and len(color) >= 3:
                    sampled_colors.append(color[:3])
        
        if sampled_colors:
            # Calcul de la couleur moyenne
            avg_r = sum(c[0] for c in sampled_colors) / len(sampled_colors)
            avg_g = sum(c[1] for c in sampled_colors) / len(sampled_colors)
            avg_b = sum(c[2] for c in sampled_colors) / len(sampled_colors)
            return (int(avg_r), int(avg_g), int(avg_b))
            
    except Exception as e:
        print(f"Erreur lors de l'échantillonnage de couleur : {e}")
    
    return None

def is_point_in_triangle(point, triangle):
    """Test simple si un point est dans un triangle (coordonnées 2D)"""
    x, y = point
    x1, y1 = triangle[0]
    x2, y2 = triangle[1]
    x3, y3 = triangle[2]
    
    # Calcul des coordonnées barycentriques
    denom = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3)
    if abs(denom) < 1e-10:
        return False
    
    a = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / denom
    b = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / denom
    c = 1 - a - b
    
    return 0 <= a <= 1 and 0 <= b <= 1 and 0 <= c <= 1

def get_triangle_color(materials, material_name, base_dir, triangle_uvs, texture_coords, images_cache):
    """Récupère la couleur spécifique d'un triangle basée sur ses coordonnées UV"""
    default_color = (244, 115, 102)
    
    if not materials or material_name not in materials:
        return default_color
    
    material = materials[material_name]
    
    # Priorité 1: Couleur de texture basée sur les UVs du triangle
    if 'texture' in material and triangle_uvs and all(uv_idx is not None for uv_idx in triangle_uvs):
        texture_name = material['texture']
        
        # Cache des images pour éviter de les recharger
        if texture_name not in images_cache:
            texture_path = os.path.join(base_dir, texture_name)
            if os.path.exists(texture_path):
                try:
                    images_cache[texture_name] = Image.open(texture_path).convert('RGB')
                    print(f"Texture chargée : {texture_name}")
                except Exception as e:
                    print(f"Erreur lors du chargement de {texture_name}: {e}")
                    images_cache[texture_name] = None
            else:
                images_cache[texture_name] = None
        
        if images_cache[texture_name] is not None:
            # Récupération des coordonnées UV du triangle
            try:
                uv_coords = []
                for uv_idx in triangle_uvs:
                    if uv_idx < len(texture_coords):
                        uv_coords.append(texture_coords[uv_idx])
                    else:
                        return default_color
                
                # Échantillonnage de la couleur du triangle
                triangle_color = sample_triangle_color(images_cache[texture_name], uv_coords)
                if triangle_color:
                    return triangle_color
                    
            except Exception as e:
                print(f"Erreur lors de l'échantillonnage UV : {e}")
    
    # Priorité 2: Couleur définie dans le .mtl
    if 'color' in material:
        return material['color']
    
    return default_color

def format_float(value, precision=6):
    """Formate un float en évitant la notation scientifique"""
    # Arrondir à la précision donnée
    rounded = round(float(value), precision)
    
    # Si la valeur est très petite, la mettre à zéro
    if abs(rounded) < 1e-10:
        rounded = 0.0
    
    # Formatage avec le nombre de décimales spécifié
    formatted = f"{rounded:.{precision}f}"
    
    # Suppression des zéros inutiles à la fin
    if '.' in formatted:
        formatted = formatted.rstrip('0').rstrip('.')
    
    return formatted

def write_rt_file(vertices, texture_coords, faces, materials, base_dir, output_path, default_color=(244, 115, 102)):
    """Écrit le fichier .rt avec les triangles et couleurs spécifiques à chaque triangle"""
    images_cache = {}  # Cache pour éviter de recharger les images
    
    try:
        with open(output_path, 'w') as file:
            print(f"Conversion de {len(faces)} triangles...")
            triangle_count = 0
            
            for face_data in faces:
                if isinstance(face_data, tuple) and len(face_data) == 2:
                    triangle_data, material_name = face_data
                else:
                    triangle_data, material_name = face_data, None
                
                # Extraction des données du triangle
                if isinstance(triangle_data, dict):
                    face = triangle_data['vertices']
                    triangle_uvs = triangle_data['uvs']
                else:
                    face = triangle_data
                    triangle_uvs = None
                
                v1_idx, v2_idx, v3_idx = face
                
                # Vérification des indices
                if (v1_idx >= len(vertices) or v2_idx >= len(vertices) or 
                    v3_idx >= len(vertices) or v1_idx < 0 or v2_idx < 0 or v3_idx < 0):
                    print(f"Attention : indices invalides ignorés {face}")
                    continue
                
                v1 = vertices[v1_idx]
                v2 = vertices[v2_idx]
                v3 = vertices[v3_idx]
                
                # Récupération de la couleur spécifique au triangle
                color = get_triangle_color(materials, material_name, base_dir, 
                                         triangle_uvs, texture_coords, images_cache)
                if color is None:
                    color = default_color
                
                # Formatage des coordonnées pour éviter la notation scientifique
                v1_str = f"{format_float(v1[0])},{format_float(v1[1])},{format_float(v1[2])}"
                v2_str = f"{format_float(v2[0])},{format_float(v2[1])},{format_float(v2[2])}"
                v3_str = f"{format_float(v3[0])},{format_float(v3[1])},{format_float(v3[2])}"
                
                # Format : tr x1,y1,z1 x2,y2,z2 x3,y3,z3 r,g,b
                line = f"tr\t{v1_str}\t{v2_str}\t{v3_str}\t{color[0]},{color[1]},{color[2]}\n"
                file.write(line)
                
                triangle_count += 1
                if triangle_count % 1000 == 0:
                    print(f"Traité : {triangle_count} triangles...")
                
        print(f"Fichier {output_path} créé avec succès !")
        print(f"Total : {triangle_count} triangles convertis")
        print("✓ Formatage numérique : pas de notation scientifique")
        
        # Fermeture des images en cache
        for img in images_cache.values():
            if img:
                img.close()
        
    except Exception as e:
        print(f"Erreur lors de l'écriture du fichier : {e}")

def convert_obj_to_rt(input_path, output_path=None, color=(244, 115, 102)):
    """Fonction principale de conversion avec couleurs par triangle"""
    
    # Génération automatique du nom de sortie si non spécifié
    if output_path is None:
        base_name = os.path.splitext(input_path)[0]
        output_path = base_name + '.rt'
    
    base_dir = os.path.dirname(input_path)
    
    print(f"Conversion de {input_path} vers {output_path}...")
    print("Mode : Couleur spécifique par triangle basée sur les coordonnées UV")
    
    # Parse le fichier OBJ
    vertices, texture_coords, faces, materials = parse_obj_file(input_path)
    
    if vertices is None or faces is None:
        return False
    
    print(f"Modèle chargé :")
    print(f"  - {len(vertices)} vertices")
    print(f"  - {len(texture_coords)} coordonnées UV")
    print(f"  - {len(faces)} triangles")
    
    if materials:
        print(f"  - Matériaux trouvés : {list(materials.keys())}")
        for mat_name, mat_data in materials.items():
            if 'texture' in mat_data:
                print(f"    * {mat_name} -> texture: {mat_data['texture']}")
    
    # Écrit le fichier RT
    write_rt_file(vertices, texture_coords, faces, materials, base_dir, output_path, color)
    return True

def main():
    """Point d'entrée du programme"""
    if len(sys.argv) < 2:
        print("Usage : python obj_to_rt.py <fichier.obj> [fichier_sortie.rt] [r,g,b]")
        print("Exemple : python obj_to_rt.py model.obj")
        print("Exemple : python obj_to_rt.py model.obj output.rt")
        print("Exemple : python obj_to_rt.py model.obj output.rt 255,0,0")
        print("")
        print("NOUVEAU : Couleur par triangle basée sur les coordonnées UV !")
        print("Le programme extrait maintenant la couleur spécifique de chaque triangle")
        print("depuis sa zone correspondante sur la texture.")
        return
    
    input_file = sys.argv[1]
    
    # Fichier de sortie optionnel
    output_file = sys.argv[2] if len(sys.argv) > 2 else None
    
    # Couleur de fallback optionnelle
    color = (244, 115, 102)  # Couleur par défaut
    
    if len(sys.argv) > 3:
        try:
            color_parts = sys.argv[3].split(',')
            if len(color_parts) == 3:
                color = (int(color_parts[0]), int(color_parts[1]), int(color_parts[2]))
            else:
                print("Format de couleur invalide, utilisation de la couleur par défaut")
        except ValueError:
            print("Format de couleur invalide, utilisation de la couleur par défaut")
    
    # Vérification des dépendances
    try:
        import PIL
        import numpy as np
        print("✓ Pillow et numpy détectés - Extraction de couleur par triangle activée")
    except ImportError:
        print("ATTENTION: PIL (Pillow) et numpy requis pour l'extraction de couleur par triangle")
        print("Installation : pip install Pillow numpy")
        print("Utilisation de la couleur par défaut pour tous les triangles...")
    
    # Conversion
    success = convert_obj_to_rt(input_file, output_file, color)
    
    if success:
        print("Conversion terminée avec succès !")
        print("Chaque triangle a maintenant sa couleur spécifique basée sur sa zone de texture !")
    else:
        print("Échec de la conversion.")

if __name__ == "__main__":
    main()
