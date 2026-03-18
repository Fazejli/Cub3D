/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 19:25:04 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/18 14:31:23 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "assets.h"

#include "parser/parser.h"
#include "utils/file.h"

int	assets_init(t_assets *assets, const char *file_path)
{
	t_file	file;

	if (!assets || !file_path)
		return (1);
	if (!is_valid_name(file_path))
		return (1);
	if (map_file(&file, file_path))
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
