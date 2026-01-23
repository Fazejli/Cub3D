/* ************************************************************************** */
/*                                   DEBUG.H                                  */
/*   Header de debug à placer dans inc/debug.h                               */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "cub3d.h"

/* Debug functions */
void	print_separator(char *title);
void	debug_textures(t_data *data);
void	debug_colors(t_data *data);
void	debug_player(t_data *data);
void	debug_map(t_data *data);
void	debug_full(t_data *data);

#endif