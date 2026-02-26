/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:11:57 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/26 13:14:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include <stdint.h>
# include "options/options.h"

typedef struct s_gfx {
	void		*mlx;
	void		*win;
}	t_gfx;

typedef struct s_image {
	void		*ptr;
	uint32_t	*data;
	uint32_t	width; // investigate the usefulness (vs linesz)
	uint32_t	height;
	uint32_t	bpp;
	uint32_t	linesz;
}	t_image;

// void		set_pixel(uint32_t x, uint32_t y, uint32_t color, t_image *img);
// void		add_pixel(uint32_t x, uint32_t y, uint32_t color, t_image *img);
// uint32_t	get_pixel(uint32_t x, uint32_t y, t_image *img);
// void		scale_pixel(uint32_t x, uint32_t y, uint32_t c, int scale, t_image *dst);
// uint32_t	blend_colors(uint32_t src_c, uint32_t dst_c, float t);

// void		clear_image(t_image *img);
// void		free_image(void *mlx, t_image *img);
// t_image		*make_blank_image(void *mlx, int width, int height);
// t_image		*get_image_from_xpm(void *mlx, char *file);

int		gfx_init(t_gfx *gfx, const t_options *opt);
void	gfx_deinit(t_gfx *gfx);

void	gfx_present(const t_gfx *gfx, const t_image *img);
void	gfx_loop(t_gfx *gfx, int (*fn)(void), void *userdata);

int		gfx_image_create(const t_gfx *gfx, t_image *img,
			uint32_t width, uint32_t height);

#endif
