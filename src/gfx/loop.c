/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:56:04 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/20 13:56:44 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"

void	gfx_loop(t_gfx *gfx, int (*fn)(void), void *userdata)
{
	mlx_loop_hook(gfx->mlx, fn, userdata);
	mlx_loop(gfx->mlx);
}
