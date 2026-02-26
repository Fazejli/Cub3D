/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:05:44 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/26 13:08:00 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

typedef enum e_entity_type {
	ENTITY_DOOR,
}	t_entity_type;

// temp
typedef struct s_v2f {
	float	x;
	float	y;
}	t_v2f;

typedef struct s_door {
	float	state;
}	t_door;

typedef struct s_player
{
	t_v2f	pos;
	float	yaw;
	float	fov;
}	t_player;

typedef struct __attribute__((aligned(8))) s_entity
{
	int		type;
	t_v2f	pos;

	union {
		t_door	door;
	};
}	t_entity;

#endif
