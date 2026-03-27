/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 22:01:21 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/27 10:46:23 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "utils.h"

long	get_timestamp_us(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000000l + ts.tv_nsec / 1000l);
}
