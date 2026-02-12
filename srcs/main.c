/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:37:02 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/12 14:35:12 by fadzejli         ###   ########.fr       */
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
	printf("=> Parsing successful!\n");
	init_game(&game, &data);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1024, 1024, "Cub3D");
	game.img = mlx_new_image(game.mlx, get_width(data.map), get_height(data.map));
	mlx_loop(game.mlx);
	free_data(&data);
	return (0);
}
