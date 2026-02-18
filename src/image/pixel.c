/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:01:42 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/16 17:29:35 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "image.h"

/**
 * @brief Sets a given color value to a pixel.
 *
 * @param x horizontal coordinates
 * @param y vertical coordinates
 * @param c Color
 * @param image Image pointer
 */
void	set_pixel(uint32_t x, uint32_t y, uint32_t color, t_image *img)
{
	char	*dst;

	if (!img || x >= img->pxl_w || y >= img->pxl_h)
		return ;
	if (color > 0xFFFFFF)
		color = 0xFFFFFF;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pxl / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief Adds a given color value to a pixel.
 *
 * @param x horizontal coordinates
 * @param y vertical coordinates
 * @param c Color
 * @param img Image pointer
 */
void	add_pixel(uint32_t x, uint32_t y, unsigned int color, t_image *img)
{
	char	*dst;

	if (!img || x >= img->pxl_w || y >= img->pxl_h || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pxl / 8));
	color += *(unsigned int *)dst;
	if (color > 0xFFFFFF)
		color = 0xFFFFFF;
	*(unsigned int *)dst = color;
}

/**
 * @brief Gives the given color value of a pixel.
 *
 * @param x horizontal coordinates
 * @param y vertical coordinates
 * @param img Image pointer
 * @return Color value of the pixel.
 */
uint32_t	get_pixel(uint32_t x, uint32_t y, t_image *img)
{
	char	*src;

	if (!img || x >= img->pxl_w || x < 0 || y >= img->pxl_h || y < 0)
		return (0);
	src = img->addr + y * img->line_length + x * (img->bits_per_pxl / 8);
	return (*(uint32_t *)src);
}

/** 
 * @brief Scales a pixel by a given factor and color values.
 */
void	scale_pixel(uint32_t x, uint32_t y, uint32_t c, int scale, t_image *dst)
{
	uint32_t	i;
	uint32_t	j;

	if (!dst)
		return ;
	j = 0;
	while (j < y + scale)
	{
		i = x;
		while (i < x + scale)
		{
			set_pixel(i, j, c, dst);
			i++;
		}
		j++;
	}
}

uint32_t	blend_colors(uint32_t src_c, uint32_t dst_c, float t)
{
	int	r;
	int	g;
	int	b;

	if (t < 0)
		return (src_c);
	if (t > 1)
		return (dst_c);
	r = ((1 - t) * ((src_c >> 16) & 0xFF)) + (t * ((dst_c >> 16) & 0xFF));
	g = ((1 - t) * ((src_c >> 8) & 0xFF)) + (t * ((dst_c >> 8) & 0xFF));
	b = ((1 - t) * (src_c & 0xFF)) + (t * (dst_c & 0xFF));
	return (r << 16 | g << 8 | b);
}
