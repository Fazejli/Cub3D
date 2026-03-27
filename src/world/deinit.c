/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:19:40 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/27 10:48:04 by macarnie         ###   ########.fr       */
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
