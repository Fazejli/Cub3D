/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:05:30 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/20 01:57:41 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include "libft.h"

int	mess_error(const char *msg)
{
	// todo: replace with ft_dprintf
	if (msg)
		dprintf(2, "Error %s\n", msg);
	else
		perror("Error");
	return (1);
}

int	check_arg(const char *filename)
{
	size_t	len;

	if (!filename)
		return (1);
	len = __builtin_strlen(filename);
	if (len < 5)
		return (1);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (1);
	return (0);
}
