/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:57:03 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/13 11:02:06 by fadzejli         ###   ########.fr       */
/*                                                                            */
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