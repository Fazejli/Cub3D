/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:34:49 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/18 15:00:36 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

static int	parse_mode(t_options *opt, const char *value)
{
	(void)value;
	opt->mode = RENDER_DDA;
	dprintf(2, "Warning: --mode option ignored\n");
	return (0);
}

static int	parse_threads(t_options *opt, const char *value)
{
	uint64_t	threads;
	char		*end;

	threads = strtoul(value, &end, 10);
	if (threads > 255 || *end != '\0')
	{
		dprintf(2, "Error: Invalid thread count (max 255)\n");
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
	{.name = "--mode", .short_name = "-m", .parse = parse_mode},
	{.name = "--threads", .short_name = "-j", .parse = parse_threads},
};

static void	init_default_values(t_options *opt)
{
	opt->thread_count = -1;
	opt->mode = RENDER_DDA;
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
		if (!argv[i + 1] || !options[j].parse(opt, argv[i + 1]))
			return (1);
		i += 2;
	}
	printf("%s\n", argv[i]);
	return (argv[i] == nullptr);
}
