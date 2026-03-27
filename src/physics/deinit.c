/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:49:01 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/27 10:49:36 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/error.h"

#include "physics.h"

void	physics_deinit(t_physics *p)
{
	if (!p)
		return ;
	atomic_store(&p->running, false);
	if (p->thread && pthread_join(p->thread, NULL) != 0)
		print_error(MOD_PHYSICS, ERR_PERROR, 1);
}
