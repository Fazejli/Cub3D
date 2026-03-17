/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:45:47 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/17 11:50:27 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assets/assets.h"
#include "gfx/gfx.h"

#include "engine.h"

#include <stdio.h>

void	engine_deinit(t_engine *e)
{
	gfx_deinit(&e->gfx);
	assets_deinit(&e->assets);
}
