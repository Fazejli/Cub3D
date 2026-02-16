# Cub3D

## Description

Cub3D est un projet de raycasting inspiré du célèbre jeu Wolfenstein 3D, développé dans le cadre du cursus 42. Le programme crée une vue 3D subjective à l'intérieur d'un labyrinthe à partir d'une carte 2D.

Le projet utilise la technique du **raycasting** pour simuler un environnement 3D, permettant au joueur de se déplacer dans un labyrinthe texturé avec une interface graphique fluide.

## Objectifs Pédagogiques

- Comprendre les bases du raycasting et du rendu 3D en temps réel
- Manipuler des vecteurs en 2D pour créer une illusion 3D
- Implémenter l'algorithme DDA (Digital Differential Analysis)
- Gérer les textures et leur mapping sur les murs
- Utiliser la MiniLibX pour l'affichage graphique et la gestion d'événements
- Parser et valider des fichiers de configuration complexes

## Fonctionnalités

### Partie Obligatoire

- **Vue subjective** : rendu 3D en temps réel depuis la perspective du joueur
- **Textures** : 4 textures différentes pour les murs (Nord, Sud, Est, Ouest)
- **Couleurs** : couleurs personnalisables pour le sol et le plafond
- **Déplacements** : W/A/S/D pour se déplacer, flèches pour tourner
- **Parsing** : lecture et validation de fichiers `.cub`
- **Collisions** : impossible de traverser les murs
- **Interface** : fenêtre graphique avec gestion propre de la fermeture

### Bonus (si partie obligatoire parfaite)

- Collision avec les murs (wall collision)
- Minimap affichée en temps réel
- Portes qui s'ouvrent et se ferment
- Sprites animés (objets 3D)
- Rotation avec la souris

## Compilation

```bash
make          # Compile le projet
make clean    # Supprime les fichiers objets
make fclean   # Supprime les fichiers objets et l'exécutable
make re       # Recompile entièrement le projet
make bonus    # Compile avec les bonus
```

## Utilisation

```bash
./cub3D <fichier_map.cub>
```

### Exemple

```bash
./cub3D maps/basic.cub
```

## Contrôles

### Déplacements
- **W** : Avancer
- **S** : Reculer
- **A** : Déplacement latéral gauche
- **D** : Déplacement latéral droite

### Rotation
- **←** : Tourner à gauche
- **→** : Tourner à droite

### Système
- **ESC** : Ferme le programme
- **Croix rouge** : Ferme la fenêtre

## Format de Fichier .cub

Le fichier de configuration définit les textures, couleurs et la carte du niveau.

### Textures des Murs

```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm
```

- **NO** : Texture du mur Nord (face exposée au sud)
- **SO** : Texture du mur Sud (face exposée au nord)
- **WE** : Texture du mur Ouest (face exposée à l'est)
- **EA** : Texture du mur Est (face exposée à l'ouest)
- Les chemins doivent pointer vers des fichiers `.xpm` valides

### Couleurs

```
F 220,100,0
C 225,30,0
```

- **F** : Couleur du sol (Floor) en RGB [0-255]
- **C** : Couleur du plafond (Ceiling) en RGB [0-255]

### Carte

La carte est une grille composée de caractères :

- **0** : Espace vide (sol praticable)
- **1** : Mur
- **N** : Position de départ du joueur, orienté vers le Nord
- **S** : Position de départ du joueur, orienté vers le Sud
- **E** : Position de départ du joueur, orienté vers l'Est
- **W** : Position de départ du joueur, orienté vers l'Ouest
- **espace** : Zone en dehors de la carte

### Règles de Validation

- La carte doit être entourée de murs (fermée)
- Un seul joueur (N, S, E ou W)
- Pas de caractères invalides
- Les éléments de configuration doivent précéder la carte
- Tous les éléments obligatoires doivent être présents

### Exemple de Fichier Complet

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## Structure du Projet

```
cub3D/
├── Makefile
├── README.md
├── inc/
│   ├── cub3d.h           # Header principal
│   ├── debug.h
│   ├── game.h
│   └── parser.h
├── srcs/
│   ├── main.c
│   ├── parsing/
│   │   ├── parse_colors.c
│   │   ├── parse_data.c
│   │   ├── parse_map.c
│   │   ├── parse_textures.c
│   │   ├── parse_utils.c
│   │   └── valid_map.c
│   ├── utils/
│   |   ├── cleanup.c
│   |   └── errors.c
│   └── debug/
│       └── parsing_debug.c
├── maps/                 # Fichiers .cub de scenes
│   └── basic.cub
├── textures/             # Fichiers .xpm
│   ├── north.xpm
│   ├── south.xpm
│   ├── east.xpm
│   └── west.xpm
└── libft/

```

## Normes et Contraintes

- **Norme 42** : Code respectant la norme de l'école
- **Langage** : C
- **Gestion mémoire** : Aucune fuite autorisée
- **Librairies autorisées** : 
  - MiniLibX
  - libft (personnelle)
  - math library (-lm)
  - open, close, read, write, malloc, free, perror, strerror, exit
- **Variables globales** : Une seule autorisée (généralement pour MLX)

## Gestion des Erreurs

Le programme affiche `Error\n` suivi d'un message explicite sur stderr dans les cas suivants :

### Erreurs de fichier
- Fichier `.cub` manquant ou inaccessible
- Mauvaise extension (doit être `.cub`)
- Permissions insuffisantes

### Erreurs de parsing
- Éléments de configuration manquants (NO, SO, WE, EA, F, C)
- Éléments dupliqués
- Format invalide (couleurs hors limites, chemins incorrects)

### Erreurs de carte
- Carte non fermée (pas entourée de murs)
- Caractères invalides
- Aucun joueur ou plusieurs joueurs
- Espaces dans la zone praticable

### Erreurs MLX
- Échec d'initialisation de MLX
- Échec de chargement de texture
- Échec de création d'image

### Exemple de messages
```
Error
Invalid map: not closed by walls
```

```
Error
Missing texture: NO
```

## Algorithme de Raycasting

### Principe

1. **Pour chaque colonne de l'écran** :
   - Calculer la direction du rayon correspondant
   - Utiliser l'algorithme DDA pour trouver le premier mur touché
   - Calculer la distance perpendiculaire au mur
   - Calculer la hauteur du mur à afficher
   - Déterminer quelle texture utiliser (N/S/E/W)
   - Calculer les coordonnées de texture
   - Dessiner le plafond, le mur texturé, et le sol

2. **Afficher l'image** complète sur la fenêtre

### DDA (Digital Differential Analysis)

L'algorithme DDA permet de parcourir la grille case par case jusqu'à trouver un mur :

1. Partir de la position du joueur
2. Calculer dans quelle direction avancer (stepX, stepY)
3. Calculer les distances initiales jusqu'aux lignes de grille
4. Avancer case par case (X ou Y selon la plus proche)
5. S'arrêter dès qu'on touche un mur (valeur '1' dans la carte)

## Conseils de Développement

1. **Commencer simple** : carte minimale, pas de textures au début
2. **Parser d'abord** : valider entièrement le fichier .cub avant le rendu
3. **Vue 2D** : afficher la map en vue de dessus pour débugger
4. **Couleurs avant textures** : différencier les murs N/S/E/W par couleur
5. **Tester progressivement** : raycasting → textures → mouvements → collisions
6. **Valgrind** : vérifier régulièrement les fuites mémoires
7. **Norminette** : vérifier la norme au fur et à mesure

## Ressources Utiles

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - LA référence
- Documentation MiniLibX
- [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D) - Inspiration originale
- Tutoriels sur l'algorithme DDA

## Auteurs

*Projet réalisé par fadzejli dans le cadre du cursus 42.*

---

**Ce projet a été réalisé à des fins pédagogiques. Toute copie est interdite et constitue une violation de la charte de 42.**