/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:11:57 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/19 13:29:37 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include <stdint.h>
# include "cub3d.h"

typedef struct s_image {
	void		*ptr;
	uint32_t	*data;
	uint32_t	width; // investigate the usefulness (vs linesz)
	uint32_t	height;
	uint32_t	bpp;
	uint32_t	linesz;
}	t_image;

typedef struct s_gfx {
	void		*mlx;
	void		*win;
	t_image		frame;
}	t_gfx;

int		gfx_init(t_gfx *gfx, t_options opt);
void	gfx_loop(t_gfx *gfx, int (*fn)(void), void *userdata);
void	gfx_destroy(t_gfx *gfx);

#endif
