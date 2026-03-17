/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:08:02 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/17 12:02:11 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "utils.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_printable(char c)
{
	return (c >= 32 && c < 127);
}
