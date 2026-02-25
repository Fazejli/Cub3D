/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/25 22:45:54 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minimap.h"

void draw_pixel(t_game *game, int row, int col, int color)
{
    int pixel_j;
    int pixel_i;
    int i = 0;
    int j = 0;

    pixel_j = row * MMP_PIXEL_SIZE;
    pixel_i = col * MMP_PIXEL_SIZE;
    if (pixel_j + MMP_PIXEL_SIZE > WIDTH || pixel_j < 0)
        return ;
    if (pixel_i + MMP_PIXEL_SIZE > HEIGHT || pixel_i < 0)
        return ;
    while (i < MMP_PIXEL_SIZE)
    {
        j = 0;
        while (j < MMP_PIXEL_SIZE)
        {
            game->addr[(pixel_i + i) * WIDTH + (pixel_j + j)] = color;
            j++;
        }
        i++;
    }
}

void draw_minimap(t_game *game)
{
    int i;
    int j;
    char **map;

    i = 0;
    map = game->data->map;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '1')
                draw_pixel(game, j, i, 0x000000);
            else if (map[i][j] == '0' || map[i][j] == ' ')
                draw_pixel(game, j, i, 0xFFFFFF);
            else
                draw_pixel(game, j, i, 0xFF0000);
            j++;
        }
        i++;
    }
}