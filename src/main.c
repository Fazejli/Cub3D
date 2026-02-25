/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:37:02 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/25 04:09:44 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "cub3d.h"
#include "game.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "threads/threads.h"
#include "utils/error.h"

__attribute__((__noreturn__))
void	game_destroy(t_game *game, int exit_code)
{
	(void)game;
	exit(exit_code);
}

static bool	check_arg(const char *arg)
{
	size_t	len;

	if (!arg)
		return (true);
	len = ft_strlen(arg);
	if (len < 5)
		return (true);
	return (ft_strncmp(arg + len - 4, ".cub", 4) != 0);
}

int	main(
	__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv)
{
	t_game	game;
	t_data	data;

	ft_memset(&game, 0, sizeof(t_game));
	if (options_init(&game.opt, argc, argv))
	{
		print_error(loc(F, L), ERR_INVALID_OPT, 1);
		game_destroy(&game, 1);
	}
	if (threadpool_init(&game.pool, game.opt.thread_count))
	{
		print_error(loc(F, L), ERR_BAD_THREAD, 1);
		game_destroy(&game, 1);
	}
	// todo: refactor
	if (check_arg(argv[argc - 1]))
		return (print_error(loc(F, L), ERR_INVALID_NAME, 1));
	if (parse_data(&data, argv[argc - 1]))
		return (free_data(&data), 1);
	if (init_game(&game, &data))
		return (print_error(loc(F, L), ERR_PERROR, 1));
	mlx_loop(game.mlx);
	free_data(&data);
	return (0);
}
