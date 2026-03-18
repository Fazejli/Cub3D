/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:18:40 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/18 20:35:03 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"

#include "gfx.h"

#if defined (__linux__)

void	gfx_deinit(t_gfx *gfx)
{
	if (!gfx)
		return ;
	if (gfx->win)
	{
		mlx_destroy_window(gfx->mlx, gfx->win);
		gfx->win = NULL;
	}
	if (gfx->mlx)
	{
		mlx_destroy_display(gfx->mlx);
		free(gfx->mlx);
		gfx->mlx = NULL;
	}
}

#elif defined(__APPLE__)

void	gfx_deinit(t_gfx *gfx)
{
	if (!gfx)
		return ;
	if (gfx->win)
	{
		mlx_destroy_window(gfx->mlx, gfx->win);
		gfx->win = NULL;
	}
	if (gfx->mlx)
		gfx->mlx = NULL;
}

#endif
