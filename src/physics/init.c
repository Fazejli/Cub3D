/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:46:03 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/24 22:47:59 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "utils/utils.h"
#include <time.h>

__attribute__((always_inline))
inline void	sleep_ns(long ns)
{
	struct timespec	ts;

	ts.tv_sec = 0;
	ts.tv_nsec = ns;
	nanosleep(&ts, NULL);
}

static void	*physics_thread(t_physics *p)
{
	long			last_time_us;
	float			accumulator;
	const float		dt = 1.0f / 128.0f;
	long			now_us;
	float			elapsed_s;

	last_time_us = get_timestamp_us();
	accumulator = 0.0f;
	while (1)
	{
		now_us = get_timestamp_us();
		elapsed_s = (float)(now_us - last_time_us) / 1000000.0f;
		last_time_us = now_us;
		accumulator += elapsed_s;
		while (accumulator >= dt)
		{
			physics_update(p, dt);
			accumulator -= dt;
		}
		sleep_ns(1000L);
	}
	return (NULL);
}

int	physics_init(t_physics *p)
{
	atomic_store(&p->ready, 1);
	return (pthread_create(&p->thread, NULL,
			(void *(*)(void *))(intptr_t)physics_thread, p));
}
