/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:08:33 by fadzejli          #+#    #+#             */
/*   Updated: 2025/04/29 17:49:00 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *srce, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;
	int				i;

	if (!dest && !srce)
		return (0);
	i = 0;
	dst = (unsigned char *)dest;
	src = (unsigned char *)srce;
	if (dst > src)
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			dst[i] = src[i];
			i--;
		}
		return (dst);
	}
	while (i < (int)n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
