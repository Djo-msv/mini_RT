import random

def load_obj(filepath):
    vertices = []
    triangles = []

    with open(filepath, 'r') as f:
        for line in f:
            if line.startswith('v '):
                _, x, y, z = line.strip().split()
                vertices.append((float(x), float(y), float(z)))
            elif line.startswith('f '):
                parts = line.strip().split()
                indices = [int(p.split('/')[0]) - 1 for p in parts[1:]]

                if len(indices) == 3:
                    # triangle direct
                    a, b, c = [vertices[i] for i in indices]
                    triangles.append((a, b, c))
                elif len(indices) == 4:
                    # quad → deux triangles
                    a, b, c, d = [vertices[i] for i in indices]
                    triangles.append((a, b, c))
                    triangles.append((a, c, d))
                else:
                    print(f"⚠️ Face with {len(indices)} vertices ignored (not triangle or quad)")
    return triangles

def export_to_rt(triangles, output_file, random_colors=False):
    with open(output_file, 'w') as f:
        for a, b, c in triangles:
            if random_colors:
                color = (
                    random.randint(100, 255),
                    random.randint(100, 255),
                    random.randint(100, 255)
                )
            else:
                color = (255, 255, 255)

            line = f"tr\t{a[0]},{a[1]},{a[2]}\t{b[0]},{b[1]},{b[2]}\t{c[0]},{c[1]},{c[2]}\t{color[0]},{color[1]},{color[2]}\n"
            f.write(line)

# Exemple d’utilisation
if __name__ == "__main__":
    obj_file = "Orangutan.obj"   # <-- mets ton fichier ici
    rt_file = "scene.rt"
    triangles = load_obj(obj_file)
    export_to_rt(triangles, rt_file, random_colors=True)
    print(f"✅ Exporté {len(triangles)} triangles dans {rt_file}")

