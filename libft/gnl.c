/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:02:16 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/12 12:02:27 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clear_gnl(void)
{
	(void)gnl(-1);
}

static char	*join_free(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

static int	read_buffer(int fd, char *buf, int *pos, int *bytes)
{
	*bytes = read(fd, buf, BS);
	*pos = 0;
	if (*bytes <= 0)
	{
		*bytes = 0;
		*pos = 0;
		return (0);
	}
	buf[*bytes] = '\0';
	return (1);
}

static char	*process_char(char *line, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	return (join_free(line, temp));
}

char	*gnl(int fd)
{
	static char	buf[BS + 1];
	static int	pos = 0;
	static int	bytes = 0;
	char		*line;

	line = NULL;
	while (1)
	{
		if (pos >= bytes)
			if (!read_buffer(fd, buf, &pos, &bytes))
				break ;
		line = process_char(line, buf[pos++]);
		if (!line)
			return (NULL);
		if (buf[pos - 1] == '\n')
			break ;
	}
	return (line);
}
