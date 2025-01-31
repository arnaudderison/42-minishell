import os

def lister_fichiers(dossier):
    chemins_fichiers = []
    for racine, _, fichiers in os.walk(dossier):
        for fichier in fichiers:
            chemins_fichiers.append(os.path.join(racine, fichier))
    return chemins_fichiers

# Récupérer le répertoire où se trouve le script
dossier = os.getcwd()  # os.getcwd() renvoie le répertoire de travail actuel (dossier où le script est exécuté)
fichiers = lister_fichiers(dossier)

# Affichage des chemins de fichiers
for chemin in fichiers:
    print(chemin)

# Sauvegarde dans un fichier texte (facultatif)
with open('chemins_fichiers.txt', 'w') as f:
    for chemin in fichiers:
        f.write(chemin + '\n')
