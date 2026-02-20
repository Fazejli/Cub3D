/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:16:51 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/20 13:50:47 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "common.h"
# include "gfx/gfx.h"
# include "image.h"
# include "options/options.h"
# include "threads/threads.h"
# include "world/world.h"
# include <stdatomic.h>

typedef struct s_renderer
{
	const t_gfx		*gfx;
	t_world_buffer	*world_buffer;
	t_image			framebuffers[FRAMEBUFFER_COUNT];
	t_threadpool	pool;

	atomic_int		ready_index;
	int				render_index;
	// bool MT;
}	t_renderer;

int				renderer_init(t_renderer *r, const t_options *opt);
void			renderer_deinit(t_renderer *r);

void			renderer_render(t_renderer *r);

const t_image	*renderer_get_ready_frame(const t_renderer *r);
t_image			*renderer_get_render_frame(t_renderer *r);
void			renderer_publish_frame(t_renderer *r);

#endif
