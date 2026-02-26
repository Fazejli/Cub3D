/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:51:42 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/25 11:18:14 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>

# include "utils/vectors.h"
# include "utils/utils.h"

typedef enum e_error
{
	ERR_NONE,
	ERR_NO_ARGS,
	ERR_MANY_ARGS,
	ERR_INVALID_NAME,
	ERR_MAP,
	ERR_PERROR,
	ERR_UNKNOWN,
	ERR_COUNT
}	t_error;

typedef struct s_map
{
	char		*data;
	uint32_t	width;
	uint32_t	height;
	uint32_t	player;
	t_error		error;
}	t_map;

bool		is_whitespace(char c);
bool		is_walkable(char c);
bool		is_map_char(char c);

const char	*find_map(t_file file);

t_vec3u		get_map_size(const char *map_start);

int			parser_parse(const char *file_path, t_map *map);

#endif
