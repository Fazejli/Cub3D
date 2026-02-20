/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:50:34 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/20 12:44:02 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>

void	threadpool_deinit(t_threadpool *pool)
{
	int32_t	i;

	if (!pool->threads)
		return ;
	pthread_mutex_lock(&pool->lock);
	pool->stop = 1;
	pthread_cond_broadcast(&pool->cond);
	pthread_mutex_unlock(&pool->lock);
	i = -1;
	while (++i < pool->thread_count)
		pthread_join(pool->threads[i], NULL);
	pthread_mutex_destroy(&pool->lock);
	pthread_cond_destroy(&pool->cond);
	pthread_cond_destroy(&pool->done_cond);
	free(pool->threads);
}
