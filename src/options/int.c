/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:38:58 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/24 19:29:58 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options/options.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int	options_parse_i16(t_options *opts, t_option opt, const char *const str)
{
	int64_t	value;
	char	*end;

	value = strtol(str, &end, 10);
	if (value > opt.max || value < opt.min || *end != '\0')
	{
		dprintf(2, "Error: invalid value for %s. Expected %li..%li", opt.name,
			opt.min, opt.max);
		return (1);
	}
	*(int16_t *)((void *)((char *)opts + opt.offset)) = (int16_t)value;
	return (0);
}
