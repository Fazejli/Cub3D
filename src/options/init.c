/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:39:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/20 13:57:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

static int	parse_threads(t_options *opt, const char *value)
{
	uint64_t	threads;
	char		*end;

	threads = strtoul(value, &end, 10);
	if (threads > MAX_THREADS || *end != '\0')
	{
		dprintf(2, "Error: Invalid thread count (max %i)\n", MAX_THREADS);
		return (1);
	}
	opt->thread_count = (int16_t)threads;
	return (0);
}

struct s_option {
	const char *const	name;
	const char *const	short_name;
	int					(*parse)(t_options *, const char *value);
}	options[] = {
	{.name = "--threads", .short_name = "-j", .parse = parse_threads},
};

static void	init_default_values(t_options *opt)
{
	opt->thread_count = -1;
	opt->width = 800;
	opt->height = 600;
}

int	options_init(t_options *opt, int argc, char **argv)
{
	int				i;
	size_t			j;
	const char		*option;
	const size_t	opt_count = sizeof(options) / sizeof(struct s_option);

	i = 1;
	init_default_values(opt);
	while (i < argc)
	{
		option = argv[i];
		j = -1lu;
		while (++j < opt_count)
			if (strcmp(options[j].name, option) == 0
				|| strcmp(options[j].short_name, option) == 0)
				break ;
		if (j == opt_count)
			return (argv[i + 1] != nullptr);
		if (!argv[i + 1] || options[j].parse(opt, argv[i + 1]))
			return (1);
		i += 2;
	}
	return (argv[i] == nullptr);
}
