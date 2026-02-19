/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:47:32 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/19 18:56:06 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include "parser.h"
# include <stdint.h>

# if defined(__linux__)
#  include <X11/X.h>
#  include <X11/keysym.h>

enum {
	evDestroyNotify = DestroyNotify,
	evButtonPress = ButtonPress,
	evButtonPressMask = ButtonPressMask,
	evKeyPress = KeyPress,
	evKeyPressMask = KeyPressMask,
	evKeyRelease = KeyRelease,
	evKeyReleaseMask = KeyReleaseMask,
	k_w = XK_w,
	k_s = XK_s,
	k_a = XK_a,
	k_d = XK_d,
	k_space = XK_space,
	k_escape = XK_Escape,
	k_c = XK_c,
	k_left = XK_Left,
	k_right = XK_Right,
	k_up = XK_Up,
	k_down = XK_Down,
};

# elif defined(__APPLE__)

enum {
	evDestroyNotify = 17,
	evButtonPress = 4,
	evButtonPressMask = 1L << 2,
	evKeyPress = 2,
	evKeyPressMask = 1L << 0,
	evKeyRelease = 3,
	evKeyReleaseMask = 1L << 1,
	k_w = 13,
	k_s = 1,
	k_a = 0,
	k_d = 2,
	k_space = 49,
	k_esacpe = 53,
	k_c = 8,
	k_left = 123,
	k_right = 124,
	k_up = 126,
	k_down = 125,
};

# endif

enum e_dir {
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

typedef enum __attribute__((packed)) e_render_mode {
	RENDER_DDA,
}	t_render_mode;

typedef struct s_options {
	const char		**texture_names;
	uint32_t		texture_count;
	uint32_t		width;
	uint32_t		height;
	int16_t			thread_count;
	t_render_mode	mode;
	char			reserved[1];
}	t_options;

/*  Utils   */
int		check_arg(const char *filename);
int		mess_error(const char *msg);

int		options_init(t_options *opt, int argc, char **argv);

/* Cleanup  */
void	free_data(t_data *data);
void	free_map_and_player(t_data *data);
void	free_map(char **map);

#endif
