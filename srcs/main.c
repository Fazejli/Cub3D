/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:37:02 by fadzejli          #+#    #+#             */
/*   Updated: 2026/01/23 01:45:49 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#ifdef DEBUG
# include "../inc/debug.h"
#endif

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2 || (ac == 2 && !av[1]))
		return (mess_error("Wrong args format.\nExample: ./cub3D filename.cub"));
	if (!check_arg(av[1]))
		return (mess_error("Wrong file format\nExample: ./cub3D filename.cub"));
	data.fd = open(av[1], O_RDONLY);
	if (data.fd < 0)
		return(mess_error(NULL));
	if (parse_data(&data))
		return (free_data(&data), 1);
	printf("✓ Parsing successful!\n");
	#ifdef DEBUG
	debug_full(&data);
#else
	printf("Player: (%d,%d) facing %c\n",
		data.player_pos->x, data.player_pos->y, data.player_pos->pos);
#endif
	printf("Player: (%d,%d) facing %c\n",
		data.player_pos->x, data.player_pos->y, data.player_pos->pos);
	free_data(&data);
	close(data.fd);
	return (0);
}
