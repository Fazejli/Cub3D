/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:05:30 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/25 04:12:04 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "error.h"

#define MSG_LIMIT			128
#define FILE_LIMIT			16
#define INFO_LIMIT			96

#define EX_USAGE			"Example: <./cub3D filename.cub>"

static const char	*get_error_info(t_error err)
{
	static const char	*info[] = {
	[ERR_NONE] = ": Success",
	[ERR_NO_ARGS] = " : No arguments given. "EX_USAGE,
	[ERR_MANY_ARGS] = " : Too many arguments given. "EX_USAGE,
	[ERR_INVALID_NAME] = " : Invalid file name. "EX_USAGE,
	[ERR_INVALID_OPT] = " : Invalid option. "EX_USAGE,
	[ERR_BAD_THREAD] = " : Threadpool initialization failed.",
	[ERR_BAD_TEXTURE] = " : Faield to load texture.",
	[ERR_BAD_CLR_FORMAT] = " : Invalid color format.",
	[ERR_MAP] = " : Map error",
	[ERR_INVALID_CHAR] = " : Invalid character in map.",
	[ERR_PERROR] = " : System error",
	[ERR_UNKNOWN] = " : Unknown error"
	};

	if (err < 0 || err >= ERR_COUNT)
		return (info[ERR_UNKNOWN]);
	return (info[err]);
}

static size_t	get_syscontext(char *buf, t_debug dbg)
{
	size_t	i;

	i = strlcpy(buf, dbg.file, FILE_LIMIT + 1);
	if (i > FILE_LIMIT)
		i = FILE_LIMIT + strlcpy(&buf[FILE_LIMIT], "...", 4);
	if (dbg.line > 0)
	{
		buf[i++] = ':';
		//i += ft_sitoa(&buf[i], dbg.line); //to be implemented or use other func ?
		i += (size_t)snprintf(&buf[i], 10, "%i", dbg.line);
	}
	return (i);
}

static size_t	get_error_message(char *buf, t_error err, t_debug dbg)
{
	size_t	i;
	size_t	copied;

	i = strlcpy(buf, "Error\n", 7); //fancify it ?
	i += get_syscontext(&buf[i], dbg);
	copied = strlcpy(&buf[i], get_error_info(err), INFO_LIMIT + 1);
	if (copied > INFO_LIMIT)
		i += INFO_LIMIT + strlcpy(&buf[i + INFO_LIMIT], "...", 4);
	else
		i += copied;
	buf[i++] = '\n';
	buf[i] = '\0';
	return (i);
}

t_debug	loc(const char *file, int line)
{
	t_debug	dbg;

	dbg.file = file;
	dbg.line = line;
	return (dbg);
}

int	print_error(t_debug dbg, t_error err, int int_code)
{
	char	msg[MSG_LIMIT];
	size_t	size;

	if (err == ERR_NONE)
		return (0);
	if (err == ERR_PERROR)
	{
		get_syscontext(msg, dbg);
		perror(msg);
	}
	else
	{
		size = get_error_message(msg, err, dbg);
		write(2, msg, size);
	}
	return (int_code);
}
