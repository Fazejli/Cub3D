/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:49:01 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/18 17:32:40 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	physics_deinit(t_physics *p)
{
	if (!p)
		return ;
	atomic_store(&p->running, false);
	if (p->thread && pthread_join(p->thread, NULL) != 0)
		return ; //error message
}
