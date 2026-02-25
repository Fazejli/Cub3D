/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:51:42 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/25 02:50:45 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPING_H
# define MAPPING_H

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>

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

t_map	get_map(const char *file_path);

#endif
