/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:44:44 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/18 19:47:59 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "libft.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

static void	*worker_loop(void *arg)
{
	t_threadpool	*pool;
	t_task			task;

	pool = (t_threadpool *)arg;
	while (true)
	{
		pthread_mutex_lock(&pool->lock);
		while (pool->task_index >= pool->task_count && !pool->stop)
			pthread_cond_wait(&pool->cond, &pool->lock);
		if (pool->stop)
		{
			pthread_mutex_unlock(&pool->lock);
			break ;
		}
		task = pool->task_queue[pool->task_index++];
		pool->active_workers++;
		pthread_mutex_unlock(&pool->lock);
		task.fn(task.arg);
		pthread_mutex_lock(&pool->lock);
		if (--pool->active_workers == 0 && pool->task_index >= pool->task_count)
			pthread_cond_signal(&pool->done_cond);
		pthread_mutex_unlock(&pool->lock);
	}
	return (NULL);
}

int	threadpool_init(t_threadpool *pool, int worker_count)
{
	int32_t	i;

	ft_memset(pool, 0, sizeof(t_threadpool));
	pool->threads = ft_calloc((size_t)worker_count, sizeof(pthread_t));
	if (!pool->threads)
		return (1);
	pthread_mutex_init(&pool->lock, NULL);
	pthread_cond_init(&pool->cond, NULL);
	pthread_cond_init(&pool->done_cond, NULL);
	i = -1;
	while (++i < worker_count)
	{
		if (pthread_create(&pool->threads[i], NULL, worker_loop, pool) != 0)
		{
			threadpool_destroy(pool);
			return (1);
		}
		pool->thread_count++;
	}
	return (0);
}
