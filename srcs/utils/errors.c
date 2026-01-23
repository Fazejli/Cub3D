/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:05:30 by fadzejli          #+#    #+#             */
/*   Updated: 2026/01/23 02:19:27 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	mess_error(char *msg)
{
	if (msg)
	{
		ft_putstr_fd("ERROR: ", 2);
		ft_putendl_fd(msg, 2);
	}
	else
		perror("ERROR");
	exit(1);
	return (1);
}

int	check_arg(char *filename)
{
	int	len;

	if (!filename)
		return (0);
    len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

