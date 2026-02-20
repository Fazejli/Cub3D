/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:19:51 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/20 14:34:06 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

# include "world/world.h"
# include <pthread.h>
# include <stdatomic.h>

typedef struct s_physics {
	t_world_buffer	*world_buffer;
	pthread_t		thread;
	atomic_int		ready;
	char			reserved[4];
}	t_physics;

int		physics_init(t_physics *p);
void	physics_deinit(t_physics *p);

#endif
