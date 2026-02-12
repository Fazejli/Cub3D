/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:11:00 by fadzejli          #+#    #+#             */
/*   Updated: 2025/04/29 17:41:50 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (unsigned char)c)
			return ((char *)(s + len));
		len--;
	}
	return (NULL);
}
/*#include <string.h>
#include <stdio.h>
int main()
{
    const char  str[] = "abcadefagh";
    printf("Mine is %s\nOG is %s\n", ft_strrchr(str, 0), strrchr(str, 0));
    return (0);
}*/