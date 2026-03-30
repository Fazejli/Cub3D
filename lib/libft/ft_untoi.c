/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_untoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:48:27 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/30 20:06:50 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

unsigned int	ft_untoi(const char *s, size_t n)
{
	size_t	i;
	unsigned long	res;

	res = 0;
	i = 0;
	while (i < n && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	while (i < n && s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		if (res > (unsigned long)UINT_MAX)
			return (0);
		i++;
	}
	return ((unsigned int)res);
}
