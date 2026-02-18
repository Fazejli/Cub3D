This project has been created as part of the 42 curriculum by fadzejli, macarnie

# Cub3D

## Description

Cub3D is a raycasting project inspired by Wolfenstein 3D, developed as part of the 42 curriculum. It renders a first person 3D view inside a maze based on a 2D map.

It uses **raycasting** to simulate a 3D environment where the player can move inside a textured maze.

## Features

* Real time first person 3D rendering
* 4 wall textures (North, South, East, West)
* Custom floor and ceiling colors
* Movement with W, A, S, D and arrow keys
* `.cub` file parsing and validation
* Wall collision
* Proper window and exit handling

### Bonus

* Minimap
* Doors
* Animated sprites
* Mouse rotation

## Compilation

```bash
make
make clean
make fclean
make re
make bonus
```

## Usage

```bash
./cub3D <map.cub>
```

Example:

```bash
./cub3D maps/basic.cub
```

## Controls

**Movement**

* W, S, A, D: move
* Left / Right arrows: rotate

**Exit**

* ESC or window close button

## .cub File Format

Defines textures, colors, and map.

### Textures

```
NO path_to_texture
SO path_to_texture
WE path_to_texture
EA path_to_texture
```

### Colors

```
F R,G,B
C R,G,B
```

### Map

Grid characters:

* `0` empty space
* `1` wall
* `N S E W` player start position and direction
* space: outside map

Rules:

* Map must be closed by walls
* Only one player
* No invalid characters
* All configuration must appear before the map

Example:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
1000N1
111111
```

## Project Structure

```
cub3D/
inc/
srcs/
maps/
textures/
libft/
```

## Error Handling

The program prints:

```
Error
message
```

Cases include:

* Invalid or missing file
* Invalid configuration
* Invalid map
* Texture or graphics initialization failure

## Raycasting Overview

For each screen column:

* Cast a ray
* Find wall using DDA
* Compute distance
* Select texture
* Draw wall, floor, ceiling
