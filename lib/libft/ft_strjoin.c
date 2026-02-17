/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:03:08 by fadzejli          #+#    #+#             */
/*   Updated: 2025/04/29 17:41:28 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
	{
		res[i] = *(unsigned char *)(s1 + j);
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		res[i] = *(unsigned char *)(s2 + j);
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}
/*
#include <stdio.h>

int	main()
{
	char const	s1[] = " ";
	char const	s2[] = "";
	printf("%s\n", ft_strjoin(s1, s2));
	return (0);
}*/