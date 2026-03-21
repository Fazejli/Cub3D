/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:05:44 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/21 15:37:12 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include "utils/vectors.h"

typedef enum e_entity_type {
	ENTITY_DOOR,
}	t_entity_type;

typedef struct s_door {
	float	state;
}	t_door;

typedef struct __attribute__((aligned(8))) s_player
{
	t_vec2f	pos;
	t_vec2f	vel;
	float	yaw;
	float	yaw_vel;
	float	fov;
	char	reserved[4];
}	t_player;

typedef struct __attribute__((aligned(8))) s_entity
{
	int		type;
	t_vec2f	pos;

	union {
		t_door	door;
	};
}	t_entity;

#endif
