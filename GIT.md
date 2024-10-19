# Fiche récapitulative des commandes Git pour le travail en équipe

## Configuration initiale
```bash
git config --global user.name "Votre Nom"
git config --global user.email "votre.email@example.com"
```

## Cloner un dépôt
```bash
git clone <url-du-depot>
```

## Branches
```bash
# Créer une nouvelle branche
git branch <nom-de-la-branche>

# Changer de branche
git checkout <nom-de-la-branche>

# Créer et changer de branche en une seule commande
git checkout -b <nom-de-la-nouvelle-branche>

# Lister les branches
git branch
```

## Modifications et commits
```bash
# Vérifier l'état des fichiers
git status

# Ajouter des fichiers à l'index
git add <fichier>
git add .  # Ajouter tous les fichiers modifiés

# Créer un commit
git commit -m "Message de commit"

# Modifier le dernier commit
git commit --amend
```

## Synchronisation avec le dépôt distant
```bash
# Récupérer les modifications du dépôt distant
git fetch

# Fusionner les modifications distantes
git pull

# Envoyer vos modifications au dépôt distant
git push origin <nom-de-la-branche>
```

## Fusion et résolution de conflits
```bash
# Fusionner une branche dans la branche courante
git merge <nom-de-la-branche>

# Si conflit, éditer les fichiers pour résoudre manuellement
# Puis, marquer comme résolu et terminer la fusion
git add <fichier-resolu>
git commit
```

## Revue de l'historique
```bash
# Afficher l'historique des commits
git log

# Afficher les modifications d'un commit spécifique
git show <hash-du-commit>
```

## Annulation de modifications
```bash
# Annuler les modifications non indexées d'un fichier
git checkout -- <fichier>

# Réinitialiser l'index (mais conserver les modifications locales)
git reset

# Annuler le dernier commit (en conservant les modifications)
git reset HEAD~1

# Annuler complètement le dernier commit et les modifications
git reset --hard HEAD~1
```

## Bonnes pratiques
1. Faites des commits fréquents et avec des messages clairs.
2. Tirez (pull) régulièrement pour rester à jour.
3. Créez une branche pour chaque nouvelle fonctionnalité ou correction.
4. Utilisez des pull requests pour la revue de code avant la fusion.
5. Communiquez avec votre équipe sur les changements importants.