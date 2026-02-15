/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:10:21 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/15 19:57:10 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_rgb(const char *str, int *error)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	*error = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (result > 255)
			return (0);
		i++;
	}
	*error = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] != ',' && str[i] != '\n')
		*error = 1;
	return (result);
}
