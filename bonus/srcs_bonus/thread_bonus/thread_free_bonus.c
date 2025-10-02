/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_free_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmassavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:04:07 by jmassavi          #+#    #+#             */
/*   Updated: 2025/10/02 21:04:09 by jmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	*tpool_kill(t_tpool *tm)
{
	if (tm == NULL)
		return (NULL);
	pthread_mutex_lock(&(tm->work_mutex));
	tm->work_first = NULL;
	tm->stop = true;
	pthread_cond_broadcast(&(tm->work_cond));
	pthread_mutex_unlock(&(tm->work_mutex));
	pthread_mutex_lock(&(tm->work_mutex));
	while (tm->thread_cnt != 1)
	{
		pthread_mutex_unlock(&(tm->work_mutex));
		usleep(100);
		pthread_mutex_lock(&(tm->work_mutex));
	}
	pthread_mutex_unlock(&(tm->work_mutex));
	pthread_mutex_destroy(&(tm->work_mutex));
	pthread_cond_destroy(&(tm->work_cond));
	pthread_cond_destroy(&(tm->working_cond));
	free_pool(tm);
	return (NULL);
}

void	*tpool_destroy(t_tpool *tm)
{
	t_tpool_work	*work;
	t_tpool_work	*work2;

	if (tm == NULL)
		return (NULL);
	pthread_mutex_lock(&(tm->work_mutex));
	work = tm->work_first;
	while (work != NULL)
	{
		work2 = work->next;
		tpool_work_destroy(work);
		work = work2;
	}
	tm->work_first = NULL;
	tm->stop = true;
	pthread_cond_broadcast(&(tm->work_cond));
	pthread_mutex_unlock(&(tm->work_mutex));
	tpool_wait(tm);
	pthread_mutex_destroy(&(tm->work_mutex));
	pthread_cond_destroy(&(tm->work_cond));
	pthread_cond_destroy(&(tm->working_cond));
	free_pool(tm);
	return (NULL);
}
