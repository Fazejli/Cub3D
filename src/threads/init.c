/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:44:44 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/17 19:58:01 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "libft.h"
#include <stdint.h>

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
	return (nullptr);
}

int	threadpool_init(t_threadpool *pool, int worker_count)
{
	int32_t	i;

	ft_memset(pool, 0, sizeof(t_threadpool));
	pool->threads = ft_calloc(worker_count, sizeof(pthread_t));
	if (!pool->threads)
		return (1);
	pthread_mutex_init(&pool->lock, nullptr);
	pthread_cond_init(&pool->cond, nullptr);
	pthread_cond_init(&pool->done_cond, nullptr);
	i = -1;
	while (++i < worker_count)
	{
		if (pthread_create(&pool->threads[i], nullptr, worker_loop, pool) != 0)
		{
			threadpool_destroy(pool);
			return (1);
		}
		pool->thread_count++;
	}
	return (0);
}
