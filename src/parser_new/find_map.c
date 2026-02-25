/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 02:52:17 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/25 02:53:16 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "../mapping_internal.h"

const char	*find_map(t_file file)
{
	const char	*map_start;
	int			i;

	map_start = file.data;
	while (map_start && map_start < file.data + file.size)
	{
		if (*map_start == '\n')
			map_start++;
		else if (is_map_char(*map_start))
			return (map_start);
		else if (*map_start == ' ')
		{
			i = 0;
			while (map_start[i] && map_start[i] == ' ')
				i++;
			if (is_map_char(map_start[i]))
				return (map_start);
			return (NULL);
		}
		else
			map_start = memchr(map_start, '\n',
			file.data + file.size - map_start);
	}
	return (NULL);
}
