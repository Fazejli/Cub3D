/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:37:02 by fadzejli          #+#    #+#             */
/*   Updated: 2026/01/21 19:36:07 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	mess_error(char *str)
{
	if (errno)
		perror("ERROR");
	else
		ft_putendl_fd(str, 2);
	exit(1);
	return (1);
}

int	check_arg(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (str[len])
	{
		if (str[len] == 't' && str[len - 1] == 'r' && str[len - 2] == '.')
			return (1);
		break ;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	fd;

	if (ac != 2 || (ac == 2 && !av[1]))
		return (mess_error("Wrong args format.\nExample: ./miniRT file.rt"));
	if (!check_arg(av[1]))
		return (mess_error("Wrong file format\nExample: ./miniRT file.rt"));
	fd = open (av[1], O_RDONLY);
	if (fd < 0)
		return(close(fd), mess_error(NULL);
	return (0);
}
