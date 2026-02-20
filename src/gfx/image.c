/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:47:55 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/20 14:04:38 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"

int	gfx_image_create(const t_gfx *gfx, t_image *img,
		uint32_t width, uint32_t height)
{
	img->ptr = mlx_new_image(gfx->mlx, (int)width, (int)height);
	if (!img->ptr)
		return (1);
	img->data = (uint32_t *)(void *)mlx_get_data_addr(img->ptr,
			(int *)&img->bpp, (int *)&img->linesz, &(int){0});
	img->width = width;
	img->height = height;
	return (0);
}
