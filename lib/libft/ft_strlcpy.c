/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:27:59 by fadzejli          #+#    #+#             */
/*   Updated: 2025/04/29 17:41:33 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (n == 0)
		return (len);
	while (src[i] && i < (n - 1))
	{
		dst[i] = src[i];
		i++;
	}
	if (i < n)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (len);
}
