/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:47:32 by fadzejli          #+#    #+#             */
/*   Updated: 2026/01/21 19:10:33 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "parser.h"
# include "game.h"
# include "debug.h"

typedef struct s_pos
{
    int x;
    int y;
    char pos;
} t_pos;

typedef struct s_data
{
    char *t_north;
    char *t_south;
    char *t_west;
    char *t_east;

    int floor_color;
    int ceiling_color;

    char **map;
    t_pos *player_pos;
    int fd;
} t_data;

/*  Utils   */
int	check_arg(char *filename);
int	mess_error(char *msg);

/* Cleanup  */
void	free_data(t_data *data);
void	free_map_and_player(t_data *data);
void	free_map(char **map);
void	free_split(char **split);

#endif
