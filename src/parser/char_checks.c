/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 02:30:40 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/25 11:09:11 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_whitespace(char c)
{
	return (c == '\n' || c == '\0');
}

bool	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_map_char(char c)
{
	return (is_walkable(c) || c == '1');
}
