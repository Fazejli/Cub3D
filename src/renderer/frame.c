/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:11:20 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/27 11:07:53 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx/gfx.h"
#include "renderer.h"
#include <stdatomic.h>

const t_image	*renderer_get_ready_frame(const t_renderer *r)
{
	const int	idx = atomic_load(&r->ready_index);

	return (r->framebuffers[idx]);
}

t_image	*renderer_get_render_frame(t_renderer *r)
{
	return (r->framebuffers[r->render_index]);
}

void	renderer_publish_frame(t_renderer *r)
{
	atomic_store(&r->ready_index, r->render_index);
	r->render_index ^= 1;
}
