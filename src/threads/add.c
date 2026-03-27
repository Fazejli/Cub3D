/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:42:01 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/27 10:43:11 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"

void	threadpool_add(t_threadpool *pool, t_task_fn fn, void *arg)
{
	pthread_mutex_lock(&pool->lock);
	pool->task_queue[pool->task_count++] = (t_task){fn, arg};
	pthread_mutex_unlock(&pool->lock);
}
