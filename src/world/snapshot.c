/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snapshot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:26:26 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/25 05:31:35 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

const t_world	*world_get_ready_snapshot(const t_world_buffer *wb)
{
	const int	idx = atomic_load(&wb->ready_index);

	return (&wb->worlds[idx]);
}

t_world	*world_get_write_snapshot(t_world_buffer *wb)
{
	return (&wb->worlds[wb->write_index]);
}

void	world_publish_snapshot(t_world_buffer *wb)
{
	const int	prev_ready = atomic_load(&wb->ready_index);

	atomic_store(&wb->ready_index, wb->write_index);
	wb->write_index = (wb->write_index + 1) % WORLD_COUNT;
	if (wb->write_index == prev_ready)
		wb->write_index = (wb->write_index + 1) % WORLD_COUNT;
}
