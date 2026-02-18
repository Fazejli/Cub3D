/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:37:02 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 13:48:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "errors.h"
#include "mlx.h"
#include <stdlib.h>
#include "libft.h"

__attribute__((__noreturn__))
__attribute__((__destructor__))
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
	// if (cli_init(&game, argc, argv))
	// 	game_destroy(&game, 1);
	
	// todo: refactor
	if (argc != 2 || (argc == 2 && !argv[1]))
		return (mess_error(ARGS_ERROR));
	if (check_arg(argv[1]))
		return (mess_error(FILE_ERROR));
	if (parse_data(&data, argv[1]))
		return (free_data(&data), 1);
	if (init_game(&game, &data))
		return (mess_error(INIT_ERROR));
	mlx_loop(game.mlx);
	free_data(&data);
	return (0);
}
