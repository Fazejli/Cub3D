# Quick Start - cub3D

## 🚀 Lancement rapide

```bash
# Compiler
make

# Lancer une map simple
./cub3D maps/mandatory/simple.cub

# Lancer le labyrinthe
./cub3D maps/mandatory/maze.cub

# Tester toutes les maps
./test_all_maps.sh
```

## 🎮 Contrôles

- **W** : Avancer
- **S** : Reculer
- **A** : Déplacer à gauche
- **D** : Déplacer à droite
- **←** : Tourner à gauche
- **→** : Tourner à droite
- **ESC** : Quitter

## 📁 Organisation

### Maps obligatoires
- `maps/mandatory/simple.cub` - Map 5x5 basique
- `maps/mandatory/basic.cub` - Map 10x5 simple
- `maps/mandatory/square.cub` - Grande map carrée
- `maps/mandatory/corridor.cub` - Couloirs
- `maps/mandatory/maze.cub` - Labyrinthe
- `maps/mandatory/island.cub` - Map avec espaces

### Maps bonus
- `maps/bonus/facing_*.cub` - Test des 4 orientations

### Maps d'erreurs
- `maps/errors/*.cub` - Tests de validation

## 🎨 Textures

Les 4 textures dans `textures/`:
- `wood_north.xpm` - Bois (Nord)
- `wood_south.xpm` - Bois (Sud)
- `brick_west.xpm` - Briques (Ouest)
- `stone_east.xpm` - Pierre (Est)

## 🔧 Personnalisation

Modifiez dans `inc/game.h`:
```c
#define WIN_WIDTH 1280     // Largeur fenêtre
#define WIN_HEIGHT 720     // Hauteur fenêtre
#define MOVE_SPEED 0.1     // Vitesse mouvement
#define ROT_SPEED 0.05     // Vitesse rotation
```

## 🐛 Debug

```bash
# Avec valgrind
valgrind --leak-check=full ./cub3D maps/mandatory/simple.cub

# Nettoyer
make fclean

# Recompiler
make re
```
