/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:15:02 by fadzejli          #+#    #+#             */
/*   Updated: 2025/04/29 17:41:52 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*new;

	start = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_calloc(0, 0));
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) != 0)
		start++;
	while (ft_strchr(set, s1[end]) != 0)
	{
		if (end <= start)
			return (ft_strdup(""));
		end--;
	}
	new = ft_substr(s1, start, end + 1 - start);
	return (new);
}
