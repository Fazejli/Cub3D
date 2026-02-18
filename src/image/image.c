/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:02:10 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/18 11:51:53 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <string.h>
#include <stdlib.h>

#include "image.h"

/**
 * @brief Clears all pixels of an image (set to black).
 *
 * @param img Image
 */
void	clear_image(t_image *img)
{
	if (img)
		memset(img->addr, 0, img->pxl_w * img->pxl_h * (img->bits_per_pxl / 8));
}

/**
 * @brief Destroys an image and frees its pointer.
 *
 * @param mlx MLX pointer
 * @param img Image
 */
void	free_image(void *mlx, t_image *img)
{
	if (!img)
		return ;
	if (mlx && img->data)
		mlx_destroy_image(mlx, img->data);
	free(img);
	img = NULL;
}

/**
 * @brief Makes a new image.
 *
 * @param mlx MLX pointer
 * @param width Width of image
 * @param height Height of image
 * @return A pointer to the new image.
 */
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
		return (free(data), NULL);
	img->addr = mlx_get_data_addr(img->data,
			&img->bits_per_pxl, &img->line_length, &img->endian);
	if (!img->addr)
		return (free_image(mlx, img), NULL);
	img->pxl_w = width;
	img->pxl_h = height;
	clear_image(img);
	return (img);
}

/**
 * @brief Gets an image from a .xpm file.
 *
 * @param mlx MLX pointer
 * @param file Filename
 *@return A pointer to the new image.
 */
t_image	*get_image_from_xpm(void *mlx, char *file)
{
	t_image	*img;

	if (!mlx || !file)
		return (NULL);
	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->data = mlx_xpm_file_to_image(mlx, file, &img->pxl_w, &img->pxl_h);
	if (!img->data)
		return (free(img), NULL);
	img->addr = mlx_get_data_addr(img->data, &img->bits_per_pxl,
			&img->line_length, &img->endian);
	if (!img->addr)
		return (free_image(mlx, img), NULL);
	return (img);
}
