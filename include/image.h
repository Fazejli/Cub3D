/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:02:18 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/18 11:52:39 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdint.h>

typedef struct s_image
{
	void	*data;
	char	*addr;
	int		pxl_w;
	int		pxl_h;
	int		bits_per_pxl;
	int		line_length;
	int		endian;
}			t_image;

void		set_pixel(uint32_t x, uint32_t y, uint32_t color, t_image *img);
void		add_pixel(uint32_t x, uint32_t y, uint32_t color, t_image *img);
uint32_t	get_pixel(uint32_t x, uint32_t y, t_image *img);
void		scale_pixel(uint32_t x, uint32_t y, uint32_t c, int scale, t_image *dst);
uint32_t	blend_colors(uint32_t src_c, uint32_t dst_c, float t);

void		clear_image(t_image *img);
void		free_image(void *mlx, t_image *img);
t_image		*make_blank_image(void *mlx, int width, int height);
t_image		*get_image_from_xpm(void *mlx, char *file);

#endif
