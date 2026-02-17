/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:36:21 by fadzejli          #+#    #+#             */
/*   Updated: 2025/04/29 17:41:17 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_str(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	j = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = i;
			while (s[j] && s[j] != c)
				j++;
			i = j;
			count++;
		}
	}
	return (count);
}

static char	**make_arr(char const *s, char **arr, char c)
{
	size_t	i;
	size_t	j;
	size_t	index;

	i = 0;
	j = 0;
	index = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = i;
			while (s[j] && s[j] != c)
				j++;
			arr[index] = ft_substr(s, i, j - i);
			i = j;
			index++;
		}
	}
	arr[index] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (0);
	arr = malloc(sizeof(char *) * (count_str(s, c) + 1));
	if (!arr)
		return (0);
	make_arr(s, arr, c);
	return (arr);
}
