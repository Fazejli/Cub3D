/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:28:34 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/27 16:14:04 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

// DO NOT CHANGE
# define FRAMEBUFFER_COUNT 2
# define WORLD_COUNT 3

# define MAX_THREADS 128

# define MAX_FPS 165
# define PHYSICS_STEP_US 7812 // ~128Hz

# define MAX_WIDTH 2880
# define MAX_HEIGHT 1920

# define MAX_ENTITIES 32

# define PI			3.14159265358979323846f

# define MOVE_SPEED			0.005f
# define ROT_SPEED			0.005f
# define MOUSE_SENSITIVITY	0.001f
# define ZOOM_SPEED			0.005f
# define FOV_MIN			0.5f // ~28.6 degrees
# define FOV_MAX			2.3f // ~131.8 degrees
# define FRICTION			0.85f

# define FOG_START	2.0f
# define FOG_END	10.0f
# define FOG_COLOR	0x0

# define ENTITY_SIZE	0.2f

# define INTERACT_DIST	2.0f
# define DOOR_SPEED		0.005f

#endif
