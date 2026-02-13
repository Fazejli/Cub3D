/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:37:02 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/13 11:41:17 by fadzejli         ###   ########.fr       */
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
	if (init_game(&game, &data))
		return (mess_error("Game init failed"));
	mlx_loop(game.mlx);
	free_data(&data);
	return (0);
}
