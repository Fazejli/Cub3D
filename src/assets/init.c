/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 19:25:04 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/17 12:16:52 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "assets.h"

#include "options/options.h"
#include "parser/parser.h"
#include "utils/file.h"

int	assets_init(t_assets *assets, const char *file_path)
{
	t_file	file;

	if (!is_valid_name(file_path))
		return (1);
	file = map_file(file_path);
	if (!file.data || file.size <= 0)
		return (1);
	if (parse_assets(assets, file.data, file.size))
	{
		assets_deinit(assets);
		unmap_file(&file);
		return (1);
	}
	unmap_file(&file);
	return (0);
}
