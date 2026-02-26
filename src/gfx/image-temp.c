/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:02:10 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/26 13:26:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <string.h>
#include <stdlib.h>

#include "gfx.h"

void	clear_image(t_image *img)
{
	if (img)
		memset(img->data, 0, img->width * img->height * (img->bpp / 8));
}

void	free_image(void *mlx, t_image *img)
{
	if (!img)
		return ;
	if (mlx && img->data)
		mlx_destroy_image(mlx, img->data);
	free(img);
	img = NULL;
}

t_image	*make_blank_image(void *mlx, int width, int height)
{
	t_image	*img;

	if (!mlx)
		return (NULL);
	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->data = mlx_new_image(mlx, width, height);
	if (!img->data)
		return (free(img), NULL);
	img->ptr = mlx_get_data_addr(img->data, (int *)&img->bpp,
		(int *)&img->linesz, &(int){0});
	if (!img->ptr)
		return (free_image(mlx, img), NULL);
	img->width = width;
	img->height = height;
	clear_image(img);
	return (img);
}

t_image	*get_image_from_xpm(void *mlx, char *file) 
{
	t_image	*img;

	if (!mlx || !file)
		return (NULL);
	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->data = mlx_xpm_file_to_image(mlx, file,
		(int *)&img->width, (int *)&img->height);
	if (!img->ptr)
		return (free(img), NULL);
	img->ptr = mlx_get_data_addr(img->data, (int *)&img->bpp,
			(int *)&img->linesz, &(int){0});
	if (!img->ptr)
		return (free_image(mlx, img), NULL);
	return (img);
}
