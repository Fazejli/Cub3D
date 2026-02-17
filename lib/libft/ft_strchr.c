/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:03:37 by fadzejli          #+#    #+#             */
/*   Updated: 2025/04/29 17:41:20 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	if ((unsigned char)c == 0)
		return (str + i);
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
int		main()
{
	printf("%s\n", strchr("", '\0'));
	printf("%s\n", ft_strchr("", '\0'));
	return (0);
}*/