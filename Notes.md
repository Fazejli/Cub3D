# Notes Cub3D - Concepts Fondamentaux

## 1. Principe du Raycasting

Le raycasting est une technique de rendu 3D simplifiée utilisée dans des jeux comme Wolfenstein 3D et Doom.

### Différence avec le Ray Tracing
- **Ray Tracing** : trace des rayons dans toutes les directions, calcule réflexions/ombres
- **Raycasting** : lance des rayons uniquement horizontalement depuis le joueur, rendu 2.5D

### Comment ça marche
1. Le joueur est dans une carte 2D (vue de dessus)
2. On lance un rayon pour chaque colonne de pixels de l'écran
3. On trouve le premier mur touché par le rayon
4. On calcule la hauteur du mur à afficher selon la distance
5. Plus le mur est loin, plus il est petit à l'écran

## 2. La Carte (Map)

### Format
La carte est une grille 2D représentée par des caractères :
- **0** : espace vide (sol)
- **1** : mur
- **N/S/E/W** : position et orientation de départ du joueur
- **espace** : zone en dehors de la carte

### Exemple de carte
```
111111
100001
10N001
100001
111111
```

### Règles importantes
- La carte doit être **fermée** (entourée de murs)
- Un seul joueur (N, S, E ou W)
- Validation stricte du format

## 3. Le Joueur

### Position
- **x, y** : coordonnées dans la grille (en float pour déplacements fluides)
- Position initiale donnée par N/S/E/W dans la carte

### Orientation (direction de vue)
- **dirX, dirY** : vecteur direction (où regarde le joueur)
- **N** : dirX=0, dirY=-1 (regarde vers le haut)
- **S** : dirX=0, dirY=1 (regarde vers le bas)
- **E** : dirX=1, dirY=0 (regarde vers la droite)
- **W** : dirX=-1, dirY=0 (regarde vers la gauche)

### Plan caméra (camera plane)
- Vecteur perpendiculaire à la direction
- Définit le champ de vision (FOV)
- Plus le plan est grand, plus le FOV est large

## 4. Algorithme DDA (Digital Differential Analysis)

### Objectif
Trouver rapidement quel mur est touché par un rayon.

### Principe
1. Partir de la position du joueur
2. Avancer le rayon case par case dans la grille
3. Vérifier à chaque case si c'est un mur (1)
4. S'arrêter dès qu'on touche un mur
5. Calculer la distance parcourue

### Variables importantes
- **stepX, stepY** : dans quelle direction on avance (+1 ou -1)
- **sideDistX, sideDistY** : distance jusqu'à la prochaine ligne verticale/horizontale
- **deltaDistX, deltaDistY** : distance entre deux lignes de grille
- **side** : est-ce qu'on a touché un mur vertical (N/S) ou horizontal (E/W) ?

## 5. Calcul de la Distance

### Distance perpendiculaire
On utilise la distance **perpendiculaire** au plan caméra, pas la distance euclidienne.

**Pourquoi ?** Pour éviter l'effet "fish-eye" (distorsion en œil de poisson).

### Formule
```
Si side == 0 (mur vertical) :
    perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX

Si side == 1 (mur horizontal) :
    perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY
```

## 6. Rendu des Murs

### Calcul de la hauteur
```
lineHeight = (int)(screenHeight / perpWallDist)
```

Plus le mur est proche (perpWallDist petit), plus lineHeight est grand.

### Calcul des points de dessin
```
drawStart = -lineHeight / 2 + screenHeight / 2
drawEnd = lineHeight / 2 + screenHeight / 2
```

On dessine de `drawStart` à `drawEnd` sur la colonne de l'écran.

### Ce qu'on dessine
1. **Plafond** : de 0 à drawStart (couleur du plafond)
2. **Mur** : de drawStart à drawEnd (texture ou couleur selon orientation)
3. **Sol** : de drawEnd à screenHeight (couleur du sol)

## 7. Les Textures

### Coordonnées de texture
- **wallX** : où exactement le rayon a touché le mur (entre 0 et 1)
- **texX** : colonne de la texture à utiliser
- **texY** : ligne de la texture pour chaque pixel

### Calcul de texX
```
wallX = (mur vertical) ? posY + perpWallDist * rayDirY
                       : posX + perpWallDist * rayDirX
wallX -= floor(wallX)  // Partie décimale seulement
texX = (int)(wallX * texWidth)
```

### Mapping texture sur le mur
Pour chaque pixel du mur :
```
step = texHeight / lineHeight
texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step
Pour chaque y de drawStart à drawEnd :
    texY = (int)texPos
    texPos += step
    color = texture[texY][texX]
```

## 8. Format de Fichier .cub

### Structure
```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

F 220,100,0
C 225,30,0

111111
100001
10N001
100001
111111
```

### Éléments
- **NO** : texture mur Nord (face sud du mur)
- **SO** : texture mur Sud (face nord du mur)
- **WE** : texture mur Ouest (face est du mur)
- **EA** : texture mur Est (face ouest du mur)
- **F** : couleur du sol (Floor) en RGB
- **C** : couleur du plafond (Ceiling) en RGB
- **Map** : grille avec 0, 1, et N/S/E/W

### Règles de parsing
- Les éléments de texture/couleur peuvent être dans n'importe quel ordre
- Doivent tous être présents AVANT la carte
- La carte doit être la dernière chose du fichier
- Lignes vides autorisées entre les éléments
- Map doit être valide (fermée, un seul joueur)

## 9. Déplacements et Rotation

### Déplacement avant/arrière
```
// Avancer (W)
if (map[posY][posX + dirX * moveSpeed] == '0')
    posX += dirX * moveSpeed
if (map[posY + dirY * moveSpeed][posX] == '0')
    posY += dirY * moveSpeed

// Reculer (S) : même chose avec -
```

### Déplacement latéral (bonus)
```
// Droite (D)
posX += planeX * moveSpeed
posY += planeY * moveSpeed

// Gauche (A)
posX -= planeX * moveSpeed
posY -= planeY * moveSpeed
```

### Rotation
On fait tourner les vecteurs direction ET plane avec une matrice de rotation :

```
// Rotation à droite (→)
oldDirX = dirX
dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed)
dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed)

oldPlaneX = planeX
planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed)
planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed)

// Rotation à gauche (←) : utiliser -rotSpeed
```

## 10. MLX (MiniLibX)

### Initialisation
```c
void    *mlx_ptr;
void    *win_ptr;
void    *img_ptr;
char    *img_data;

mlx_ptr = mlx_init();
win_ptr = mlx_new_window(mlx_ptr, width, height, "Cub3D");
img_ptr = mlx_new_image(mlx_ptr, width, height);
img_data = mlx_get_data_addr(img_ptr, &bpp, &line_len, &endian);
```

### Mettre un pixel
```c
void    put_pixel(char *img_data, int x, int y, int color)
{
    int offset;
    
    offset = (y * line_length) + (x * (bits_per_pixel / 8));
    *(unsigned int *)(img_data + offset) = color;
}
```

### Charger une texture
```c
void    *texture;
char    *tex_data;
int     tex_width;
int     tex_height;

texture = mlx_xpm_file_to_image(mlx_ptr, "path.xpm", 
                                 &tex_width, &tex_height);
tex_data = mlx_get_data_addr(texture, &bpp, &line_len, &endian);
```

### Boucle d'événements
```c
mlx_hook(win_ptr, 2, 1L<<0, key_press, &data);    // Touche pressée
mlx_hook(win_ptr, 17, 0, close_window, &data);    // Croix rouge
mlx_loop_hook(mlx_ptr, render_frame, &data);      // Rendu en boucle
mlx_loop(mlx_ptr);
```

## 11. Gestion des Touches

### Touches principales
- **W** : avancer
- **S** : reculer
- **A** : gauche (strafe, bonus)
- **D** : droite (strafe, bonus)
- **←** : tourner à gauche
- **→** : tourner à droite
- **ESC** : quitter

### Key codes (Linux)
- W = 119, S = 115, A = 97, D = 100
- ← = 65361, → = 65363
- ESC = 65307

### Key codes (MacOS)
- W = 13, S = 1, A = 0, D = 2
- ← = 123, → = 124
- ESC = 53

## 12. Structure de Données Recommandée

```c
typedef struct s_vector
{
    double  x;
    double  y;
}   t_vector;

typedef struct s_player
{
    t_vector    pos;        // Position
    t_vector    dir;        // Direction
    t_vector    plane;      // Plan caméra
}   t_player;

typedef struct s_ray
{
    t_vector    dir;        // Direction du rayon
    t_vector    sideDist;   // Distance jusqu'à prochaine case
    t_vector    deltaDist;  // Distance entre cases
    int         stepX;
    int         stepY;
    int         mapX;
    int         mapY;
    int         side;       // 0 = vertical, 1 = horizontal
    double      perpDist;   // Distance perpendiculaire
}   t_ray;

typedef struct s_texture
{
    void    *img;
    char    *data;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}   t_texture;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    void        *img;
    char        *img_data;
    char        **map;
    t_player    player;
    t_texture   textures[4];    // NO, SO, WE, EA
    int         floor_color;
    int         ceiling_color;
    int         width;
    int         height;
}   t_game;
```

## 13. Algorithme Général

```
Initialisation :
    1. Parser le fichier .cub
    2. Valider la carte
    3. Initialiser MLX
    4. Charger les textures
    5. Positionner le joueur

Boucle de jeu :
    1. Gérer les inputs (touches)
    2. Mettre à jour la position/rotation du joueur
    3. Pour chaque colonne x de l'écran :
        a. Calculer la direction du rayon
        b. Lancer DDA pour trouver le mur
        c. Calculer la distance perpendiculaire
        d. Calculer la hauteur du mur
        e. Calculer les coordonnées de texture
        f. Dessiner le plafond
        g. Dessiner le mur (avec texture)
        h. Dessiner le sol
    4. Afficher l'image (mlx_put_image_to_window)
```

## 14. Ordre de Développement

1. **Parser** : lire le .cub, stocker textures/couleurs/map
2. **Validation** : vérifier que la map est fermée
3. **MLX basique** : ouvrir fenêtre, afficher couleurs
4. **Joueur** : initialiser position et direction
5. **Raycasting basique** : murs avec couleurs différentes N/S/E/W
6. **Textures** : charger et appliquer les XPM
7. **Déplacements** : W/S + rotations
8. **Collisions** : ne pas traverser les murs
9. **Bonus** : minimap, souris, portes, etc.

## 15. Debugging Tips

- Afficher la map en 2D d'abord (vue de dessus)
- Vérifier les valeurs de dirX, dirY, planeX, planeY
- Logger la distance des murs trouvés
- Tester avec une map simple (petit carré)
- Vérifier les textures en dehors du raycasting d'abord
- Utiliser des couleurs avant les textures

## 16. Bonus Possibles

- Minimap en temps réel
- Rotation avec la souris
- Portes qui s'ouvrent/ferment
- Sprites (objets 3D)
- Collisions améliorées (sliding)
- Shadows/lighting dynamique