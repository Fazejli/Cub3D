/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:19:40 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/18 16:48:36 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "world.h"

void	world_buffer_deinit(t_world_buffer *wb)
{
	if (!wb)
		return ;
	memset(wb, 0, sizeof(t_world_buffer));
}
