/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:37:02 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/17 15:37:41 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_game	game;

	if (ac != 2 || (ac == 2 && !av[1]))
		return (mess_error(ARGS_ERROR));
	if (!check_arg(av[1]))
		return (mess_error(FILE_ERROR));
	if (parse_data(&data, av[1]))
		return (free_data(&data), 1);
	if (init_game(&game, &data))
		return (mess_error(INIT_ERROR));
	mlx_loop(game.mlx);
	free_data(&data);
	return (0);
}
