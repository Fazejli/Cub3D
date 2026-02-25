/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 03:25:02 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/25 04:03:37 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <sys/errno.h>

typedef struct s_debug
{
	const char	*file;
	int			line;

	char		reserved[4];
}				t_debug;

# define F	__FILE__
# define L	__LINE__

typedef enum e_error
{
	ERR_NONE,
	ERR_NO_ARGS,
	ERR_MANY_ARGS,
	ERR_INVALID_NAME,
	ERR_INVALID_OPT,
	ERR_BAD_THREAD,
	ERR_BAD_TEXTURE,
	ERR_BAD_CLR_FORMAT,
	ERR_MAP,
	ERR_INVALID_CHAR,
	ERR_PERROR,
	ERR_UNKNOWN, //99
	ERR_COUNT
}	t_error;

t_debug	loc(const char *file, int line);
int		print_error(t_debug dbg, t_error err, int int_code);

#endif
