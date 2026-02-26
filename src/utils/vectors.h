/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:55:10 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/25 10:56:49 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <stdint.h>

typedef struct s_vec2f {
	float	x;
	float	y;
}	t_vec2f;

typedef struct s_vec2u {
	uint32_t	x;
	uint32_t	y;
}	t_vec2u;

typedef struct s_vec3u {
	uint32_t	x;
	uint32_t	y;
	uint32_t	z;
}	t_vec3u;

#endif
