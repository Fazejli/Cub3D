#!/bin/bash

# ============================================================================
# Script de setup complet pour cub3D
# Crée toute l'arborescence et génère tous les fichiers
# ============================================================================

GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${BLUE}╔═══════════════════════════════════════╗${NC}"
echo -e "${BLUE}║     CUB3D - Setup Complet             ║${NC}"
echo -e "${BLUE}╚═══════════════════════════════════════╝${NC}"
echo ""

# ============================================================================
# Étape 1: Créer l'arborescence
# ============================================================================
echo -e "${YELLOW}[1/4]${NC} Création de l'arborescence..."

mkdir -p maps/mandatory
mkdir -p maps/bonus
mkdir -p maps/errors
mkdir -p textures
mkdir -p srcs/game

echo -e "${GREEN}✓${NC} Dossiers créés"
echo ""

# ============================================================================
# Étape 2: Créer les textures
# ============================================================================
echo -e "${YELLOW}[2/4]${NC} Création des textures..."

# Liste des fichiers de textures à copier depuis l'artifact texture_collection
TEXTURES=("wood_north.xpm" "wood_south.xpm" "brick_west.xpm" "stone_east.xpm")

echo -e "${BLUE}Info:${NC} Copiez les 4 fichiers XPM depuis l'artifact 'texture_collection':"
for tex in "${TEXTURES[@]}"; do
    echo "  - textures/$tex"
done

echo -e "${GREEN}✓${NC} Emplacement textures préparé"
echo ""

# ============================================================================
# Étape 3: Créer les maps
# ============================================================================
echo -e "${YELLOW}[3/4]${NC} Création des maps de test..."

# Map simple de test
cat > maps/mandatory/simple.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 50,50,50
C 135,206,235

111111
100001
100N01
100001
111111
EOF

# Map basique
cat > maps/mandatory/basic.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 100,100,100
C 200,200,255

1111111111
1000000001
1000N00001
1000000001
1111111111
EOF

# Map carrée
cat > maps/mandatory/square.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 80,60,40
C 180,220,255

11111111111111
10000000000001
10000000000001
10000000000001
10000N00000001
10000000000001
10000000000001
10000000000001
11111111111111
EOF

# Map couloir
cat > maps/mandatory/corridor.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 50,50,50
C 100,100,150

1111111111111111111
1000000000000000001
1011111111111111101
1000000000000000001
1011111111111111101
1000000N00000000001
1011111111111111101
1000000000000000001
1111111111111111111
EOF

# Map labyrinthe
cat > maps/mandatory/maze.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 70,70,70
C 150,180,220

11111111111111111
10000000001000001
10111111101011101
10100000001000101
10101111111110101
10100000000010101
10111111111010101
10000000000010101
11111111111010101
10000001010010101
10111101010010101
10100101010010101
10101101010010101
10101N00000000101
10101110111111101
10000000100000001
11111111111111111
EOF

# Map avec îles
cat > maps/mandatory/island.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 139,69,19
C 135,206,235

        111111111
        100000001
        100000001
111111111000000001
100000000000000001
100000000N00000001
100000000000000001
111111111000000001
        100000001
        100000001
        111111111
EOF

# Maps bonus - différentes orientations
cat > maps/bonus/facing_north.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 100,100,100
C 200,200,255

11111
10001
10N01
10001
11111
EOF

cat > maps/bonus/facing_south.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 100,100,100
C 200,200,255

11111
10001
10S01
10001
11111
EOF

cat > maps/bonus/facing_east.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 100,100,100
C 200,200,255

11111
10001
10E01
10001
11111
EOF

cat > maps/bonus/facing_west.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 100,100,100
C 200,200,255

11111
10001
10W01
10001
11111
EOF

# Maps d'erreurs
cat > maps/errors/no_player.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 100,100,100
C 200,200,255

11111
10001
10001
10001
11111
EOF

cat > maps/errors/multiple_players.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 100,100,100
C 200,200,255

11111
1N001
10S01
10001
11111
EOF

cat > maps/errors/open_map.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 100,100,100
C 200,200,255

11111
10001
10N0
10001
11111
EOF

cat > maps/errors/invalid_rgb.cub << 'EOF'
NO ./textures/wood_north.xpm
SO ./textures/wood_south.xpm
WE ./textures/brick_west.xpm
EA ./textures/stone_east.xpm

F 100,100,256
C 200,200,255

11111
10001
10N01
10001
11111
EOF

echo -e "${GREEN}✓${NC} 13 maps créées"
echo ""

# ============================================================================
# Étape 4: Afficher résumé et instructions
# ============================================================================
echo -e "${YELLOW}[4/4]${NC} Résumé de l'installation"
echo ""
echo -e "${BLUE}Structure créée:${NC}"
echo "  📁 maps/"
echo "     ├── 📁 mandatory/ (6 maps)"
echo "     ├── 📁 bonus/ (4 maps)"
echo "     └── 📁 errors/ (4 maps)"
echo "  📁 textures/ (prêt pour 4 textures XPM)"
echo "  📁 srcs/game/ (pour les fichiers d'exécution)"
echo ""

echo -e "${BLUE}Prochaines étapes:${NC}"
echo "  1. ${YELLOW}Copier les textures XPM${NC}"
echo "     Depuis l'artifact 'texture_collection' vers textures/"
echo ""
echo "  2. ${YELLOW}Copier les fichiers game${NC}"
echo "     Depuis l'artifact 'cub3d_execution' vers srcs/game/"
echo ""
echo "  3. ${YELLOW}Mettre à jour le Makefile${NC}"
echo "     Utiliser le Makefile de l'artifact 'makefile_updated'"
echo ""
echo "  4. ${YELLOW}Compiler${NC}"
echo "     $ make"
echo ""
echo "  5. ${YELLOW}Tester${NC}"
echo "     $ ./cub3D maps/mandatory/simple.cub"
echo ""

echo -e "${GREEN}✨ Setup terminé!${NC}"
echo ""

# Créer un fichier aide-mémoire
cat > QUICK_START.md << 'EOF'
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
EOF

echo -e "${GREEN}✓${NC} Fichier QUICK_START.md créé"
echo ""
echo "Consultez QUICK_START.md pour un guide rapide d'utilisation!"
echo ""