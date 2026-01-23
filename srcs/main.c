/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:37:02 by fadzejli          #+#    #+#             */
/*   Updated: 2026/01/23 12:24:10 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_game game;

	if (ac != 2 || (ac == 2 && !av[1]))
		return (mess_error("Wrong args format.\nExample: ./cub3D filename.cub"));
	if (!check_arg(av[1]))
		return (mess_error("Wrong file format\nExample: ./cub3D filename.cub"));
	data.fd = open(av[1], O_RDONLY);
	if (data.fd < 0)
		return (mess_error(NULL));
	if (parse_data(&data))
		return (free_data(&data), 1);
	printf("✓ Parsing successful!\n");
	if (init_game(&game, &data))
		return (free_data(&data), 1);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free_data(&data);
	close(data.fd);
	return (0);
}
