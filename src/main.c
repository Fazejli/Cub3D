/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:37:02 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 23:56:23 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "cub3d.h"
#include "game.h"
#include "errors.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "threads/threads.h"

__attribute__((__noreturn__))
void	game_destroy(t_game *game, int exit_code)
{
	(void)game;
	exit(exit_code);
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
		dprintf(2, "No options?\n");
		game_destroy(&game, 1);
	}
	if (threadpool_init(&game.pool, game.opt.thread_count))
	{
		dprintf(2, "Threadpool init failed\n");
		game_destroy(&game, 1);
	}
	// todo: refactor
	if (check_arg(argv[argc - 1]))
		return (mess_error(FILE_ERROR));
	if (parse_data(&data, argv[argc - 1]))
		return (free_data(&data), 1);
	if (init_game(&game, &data))
		return (mess_error(INIT_ERROR));
	mlx_loop(game.mlx);
	free_data(&data);
	return (0);
}
