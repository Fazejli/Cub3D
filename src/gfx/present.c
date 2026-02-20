/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   present.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:15:30 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/20 13:16:18 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"

void	gfx_present(const t_gfx *gfx, const t_image *img)
{
	mlx_put_image_to_window(gfx->mlx, gfx->win, img->ptr, 0, 0);
}
