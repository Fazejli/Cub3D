/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:26:02 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/17 11:53:30 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>

#include "parser_internal.h"

#include "parser.h"

#include <stdio.h>

t_section	g_sections[] = {
{
	.name = "TILES",
	.len = 5,
	.parse = parse_tiles,
	.validate = validate_tiles,
}, {
	.name = "TEXTURES",
	.len = 8,
	.parse = parse_textures,
	.validate = validate_textures,
}, {
	.name = "COLORS",
	.len = 6,
	.parse = parse_colors,
	.validate = validate_colors,
}, {
	.name = "MAP",
	.len = 3,
	.parse = parse_map,
	.validate = validate_map,
}
};

static int	is_section(t_str str)
{
	return (str.len >= 3 && str.ptr[0] == '[' && str.ptr[str.len - 1] == ']');
}

static int	get_section_fns(t_str str, t_parse_fn *p, t_validate_fn *v)
{
	size_t			i;
	const size_t	section_count = sizeof(g_sections) / sizeof(t_section);

	i = 0;
	while (i < section_count)
	{
		if (g_sections[i].len == str.len
			&& strncmp(str.ptr, g_sections[i].name, g_sections[i].len))
		{
			*p = g_sections[i].parse;
			*v = g_sections[i].validate;
			break ;
		}
		i++;
	}
	if (i == section_count)
		return (dprintf(2, "Could not find valid section: [%.*s]\n", (int)str.len, str.ptr), 1);
	return (0);
}

int	parse_assets(t_assets *assets, const char *data, size_t size)
{
	t_parser		p;
	t_str			line;
	t_parser		s;
	t_parse_fn		parse;
	t_validate_fn	validate;

	p = (t_parser){data, data + size};
	while (next_line(&p, &line, true, true))
	{
		if (!is_section(line))
			continue;
		line.ptr += 2;
		line.len -= 2;
		if (get_section_fns(line, &parse, &validate))
			return (1); //error, unknown section
		s = (t_parser){p.cur, p.cur};
		while (next_line(&p, &line, true, true) && !is_section(line))
			s.end = p.cur;
		if (parse(assets, s) || validate(assets))
			return (1);
		if (is_section(line))
			p.cur = line.ptr;
	}
	return (0);
}
