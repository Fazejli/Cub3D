/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 02:34:46 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/25 02:49:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPING_INTERNAL_H
# define MAPPING_INTERNAL_H

# include <stddef.h>

# include "mapping.h"

typedef struct s_vec2u {
	uint32_t	x;
	uint32_t	y;
}	t_vec2u;

typedef struct s_vec3u {
	uint32_t	x;
	uint32_t	y;
	uint32_t	z;
}	t_vec3u;

typedef struct s_file
{
	const char		*path;
	const char		*data;
	size_t			size;
	t_error			error;
}	t_file;

bool		is_eol(char c);
bool		is_walkable(char c);
bool		is_map_char(char c);

void		unmap_file(t_file *file);
t_file		map_file(const char *path);
const char	*find_map(t_file file);

t_vec3u		get_map_size(const char *map_start);

#endif