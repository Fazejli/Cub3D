/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:15:36 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/24 19:30:12 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options/options.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int	options_parse_u32(t_options *opts, t_option opt, const char *const str)
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
	*(uint32_t *)((void *)((char *)opts + opt.offset)) = (uint32_t)value;
	return (0);
}
