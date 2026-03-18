/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:39:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/18 14:09:15 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "options/options.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

t_option		g_options[] = {
{
	.name = "--threads",
	.short_name = "-j",
	.offset = offsetof(t_options, thread_count),
	.max = MAX_THREADS,
	.min = 0,
	.parse = options_parse_i16,
}, {
	.name = "--width",
	.short_name = "-W",
	.offset = offsetof(t_options, width),
	.max = MAX_WIDTH,
	.min = 1,
	.parse = options_parse_u32,
}, {
	.name = "--height",
	.short_name = "-H",
	.offset = offsetof(t_options, height),
	.max = MAX_HEIGHT,
	.min = 1,
	.parse = options_parse_u32,
}, {
	.name = "--fps",
	.short_name = "-f",
	.offset = offsetof(t_options, fps),
	.max = MAX_FPS,
	.min = 0,
	.parse = options_parse_i16,
}
};

static void	init_default_values(t_options *opts)
{
	opts->thread_count = -1;
	opts->width = 800;
	opts->height = 600;
	opts->fps = 60;
	opts->file_path = NULL;
}

static int	get_option(t_options *opts, const char *key, const char *value)
{
	size_t			j;
	const size_t	opt_count = sizeof(g_options) / sizeof(struct s_option);

	if (!key)
		return (1); //useless ?
	j = 0;
	while (j < opt_count)
	{
		if (strcmp(g_options[j].name, key) == 0
			|| strcmp(g_options[j].short_name, key) == 0)	
			break ;
		j++;
	}
	if (j == opt_count)
		return (1); //unknown opt
	if (!value)
		return (1); //no opt arg
	if (g_options[j].parse(opts, g_options[j], value))
		return (1); //bad opt arg
	return (0);
}

int	options_init(t_options *opts, int argc, char **argv)
{
	int				i;
	const char		*key;
	const char		*value;

	init_default_values(opts);
	i = 1;
	while (i < argc)
	{
		key = argv[i];
		if (*key != '-')
		{
			if (opts->file_path)
				return (1); //file already set
			opts->file_path = key;
			i++;
			continue ;
		}
		value = argv[i + 1];
		if (get_option(opts, key, value))
			return (1);
		i += 2;
	}
	if (!opts->file_path)
		return (1); //no map file
	return (0);
}
