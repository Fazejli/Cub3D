/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:37:21 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/18 14:06:03 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "game.h"

typedef int	(*t_hook_fn)(void);

int	hooks_keys_init(t_game *game);
int	hooks_mouse_init(t_game *game);

#endif
