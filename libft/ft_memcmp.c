/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:57:08 by fadzejli          #+#    #+#             */
/*   Updated: 2025/04/29 17:40:56 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	i;

	i = 0;
	while (i < (int)n)
	{
		if (*(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
			i++;
		else
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
	}
	return (0);
}
