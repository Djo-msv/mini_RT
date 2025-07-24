import numpy as np
import matplotlib.pyplot as plt
import re
import sys

def lire_vecteurs_depuis_fichier(nom_fichier):
    vecteurs = []
    with open(nom_fichier, 'r') as f:
        for ligne in f:
            ligne = ligne.strip()
            if not ligne:
                continue  # ignorer les lignes vides
            # chercher les floats avec ou sans signe, ex: -1.0, 0.5, - -0.3
            matches = re.findall(r'[-+]?\d*\.?\d+(?:[eE][-+]?\d+)?', ligne)
            if len(matches) != 3:
                print(f"⚠️ Ligne ignorée (mauvais format) : {ligne}")
                continue
            vecteurs.append([float(val) for val in matches])
    if not vecteurs:
        raise ValueError("Aucun vecteur valide trouvé dans le fichier.")
    return np.array(vecteurs)

def afficher_vecteurs(vecteurs):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    origine = np.array([0, 0, 0])
    couleurs = ['r', 'g', 'b', 'c', 'm', 'y', 'k']

    for i, vec in enumerate(vecteurs):
        color = couleurs[i % len(couleurs)]
        ax.quiver(*origine, *vec, color=color, linewidth=1.2)

    max_range = np.max(np.abs(vecteurs)) * 1.2
    ax.set_xlim([-max_range, max_range])
    ax.set_ylim([-max_range, max_range])
    ax.set_zlim([-max_range, max_range])
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    if len(vecteurs) <= 20:
        ax.legend([f"v{i+1}" for i in range(len(vecteurs))])

    plt.title(f"{len(vecteurs)} vecteurs 3D")
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python visualiseur_vecteurs.py vecteurs.txt")
        sys.exit(1)

    fichier = sys.argv[1]
    vecteurs = lire_vecteurs_depuis_fichier(fichier)
    afficher_vecteurs(vecteurs)

