/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:42:01 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/17 19:42:46 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"

void	threadpool_add(t_threadpool *pool, t_task_fn fn, void *arg)
{
	pthread_mutex_lock(&pool->lock);
	pool->task_queue[pool->task_count++] = (t_task){fn, arg};
	pthread_mutex_unlock(&pool->lock);
}
