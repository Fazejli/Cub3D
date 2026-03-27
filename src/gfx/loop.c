/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:56:04 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/27 10:49:24 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"

void	gfx_loop(t_gfx *gfx, int (*fn)(void), void *userdata)
{
	mlx_loop_hook(gfx->mlx, fn, userdata);
	mlx_loop(gfx->mlx);
}
