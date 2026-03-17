/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 11:56:11 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/17 11:57:37 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "utils/t_str.h"

#include "parser_internal.h"

static int	parse_u8(t_str *s, unsigned char *out)
{
	uint32_t	val;
	size_t		i;

	val = 0;
	i = 0;

	while (i < s->len && (s->ptr[i] >= '0' && s->ptr[i] <= '9'))
	{
		val = val * 10 + (uint32_t)(s->ptr[i] - '0');
		if (val > 255)
			return (1);
		i++;
	}
	if (i == 0)
		return (1);

	s->ptr += i;
	s->len -= i;
	*out = (unsigned char)val;
	return (0);
}

static int	skip_comma(t_str *line)
{
	if (line->len == 0 || *line->ptr != ',')
		return (1);
	line->ptr++;
	line->len--;
	return (0);
}

#include <stdio.h>

uint32_t	parse_rgb(t_str value)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	front_trim_str(&value);
	if (parse_u8(&value, &r))
		return (0);
	front_trim_str(&value);
	if (skip_comma(&value))
		return (0);
	front_trim_str(&value);
	if (parse_u8(&value, &g))
		return (0);
	front_trim_str(&value);
	if (skip_comma(&value))
		return (0);
	front_trim_str(&value);
	if (parse_u8(&value, &b))
		return (0);
	front_trim_str(&value);
	if (value.len != 0)
		return (0);
	if (r == 0 && g == 0 && b == 0)
		return (1); //return smallest color change value, reserve 0 black as error val
	return ((uint32_t)(r << 16 | g << 8 | b));
}
