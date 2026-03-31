/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 18:05:34 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/31 19:45:50 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internal.h"

#ifdef DEBUG

# include <stdio.h>

void	debug_print_fps(long now)
{
	static long		last_fps_time = 0;
	static int		frame_count = 0;
	double			fps;

	frame_count++;
	if (last_fps_time == 0)
		last_fps_time = now;
	if (now - last_fps_time >= 1000000L)
	{
		fps = (double)frame_count * 1000000.0
			/ (double)(now - last_fps_time);
		printf("FPS: %.2f\n", fps);
		frame_count = 0;
		last_fps_time = now;
	}
}

#else

void	debug_print_fps(long now)
{
	(void)now;
}

#endif
