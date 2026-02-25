/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:11:20 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/25 05:31:23 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "renderer.h"
#include <stdatomic.h>

const t_image	*renderer_get_ready_frame(const t_renderer *r)
{
	const int	idx = atomic_load(&r->ready_index);

	return (&r->framebuffers[idx]);
}

t_image	*renderer_get_render_frame(t_renderer *r)
{
	return (&r->framebuffers[r->render_index]);
}

void	renderer_publish_frame(t_renderer *r)
{
	atomic_store(&r->ready_index, r->render_index);
	r->render_index ^= 1;
}
