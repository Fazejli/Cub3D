/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:47:32 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 00:04:55 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include "parser.h"
# include <stdint.h>

enum e_dir : uint8_t {
	EAST,
	NORTH,
	WEST,
	SOUTH,
};

typedef struct s_pos
{
	float		x;
	float		y;
	enum e_dir	dir;

	char		reserved[3];
}	t_pos;

typedef struct s_data
{
	char		*t_north;
	char		*t_south;
	char		*t_west;
	char		*t_east;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	char		**map;
	t_pos		player_pos;
	int			fd;
}	t_data;

/*  Utils   */
int		check_arg(const char *filename);
int		mess_error(const char *msg);

/* Cleanup  */
void	free_data(t_data *data);
void	free_map_and_player(t_data *data);
void	free_map(char **map);

#endif
