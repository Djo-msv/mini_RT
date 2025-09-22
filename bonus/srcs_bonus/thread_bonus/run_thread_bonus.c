/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_thread_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:37:52 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:28:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static int	tpool_set_work(t_tpool *tm)
{
	t_tpool_work	*work;

	pthread_mutex_lock(&(tm->work_mutex));
	while (tm->work_first == NULL && !tm->stop)
		pthread_cond_wait(&(tm->work_cond), &(tm->work_mutex));
	if (tm->stop)
		return (1);
	work = tpool_work_get(tm);
	tm->working_cnt++;
	pthread_mutex_unlock(&(tm->work_mutex));
	if (work != NULL)
	{
		work->func(work->arg);
		tpool_work_destroy(work);
	}
	pthread_mutex_lock(&(tm->work_mutex));
	tm->working_cnt--;
	if (!tm->stop && tm->working_cnt == 0 && tm->work_first == NULL)
		pthread_cond_signal(&(tm->working_cond));
	pthread_mutex_unlock(&(tm->work_mutex));
	return (0);
}

void	*tpool_worker(void *arg)
{
	t_tpool		*tm;

	tm = arg;
	while (1)
	{
		if (tpool_set_work(tm))
			break ;
	}
	tm->thread_cnt--;
	pthread_cond_signal(&(tm->working_cond));
	pthread_mutex_unlock(&(tm->work_mutex));
	return (NULL);
}

void	tpool_wait(t_tpool *tm)
{
	if (tm == NULL)
		return ;
	pthread_mutex_lock(&(tm->work_mutex));
	while (1)
	{
		if (tm->work_first != NULL || (!tm->stop && tm->working_cnt != 0)
			|| (tm->stop && tm->thread_cnt != 0))
			pthread_cond_wait(&(tm->working_cond), &(tm->work_mutex));
		else
			break ;
	}
	pthread_mutex_unlock(&(tm->work_mutex));
}

bool	tpool_add_work(t_tpool *tm, t_thread_func func, void *arg)
{
	t_tpool_work	*work;

	if (tm == NULL)
		return (false);
	work = tpool_work_create(func, arg);
	if (work == NULL)
		return (false);
	pthread_mutex_lock(&(tm->work_mutex));
	if (tm->work_first == NULL)
	{
		tm->work_first = work;
		tm->work_last = tm->work_first;
	}
	else
	{
		tm->work_last->next = work;
		tm->work_last = work;
	}
	pthread_cond_broadcast(&(tm->work_cond));
	pthread_mutex_unlock(&(tm->work_mutex));
	return (true);
}

void	worker(void *arg)
{
	size_t		i;
	t_fcolor	*buffer;
	t_vec		*ray_direction;

	i = 0;
	buffer = ((t_thread_arg *)arg)->buffer_pnt;
	ray_direction = ((t_thread_arg *)arg)->ray_direction;
	while (i != ((t_thread_arg *)arg)->size)
	{
		render(buffer, *ray_direction, ((t_thread_arg *)arg)->scene);
		buffer++;
		ray_direction++;
		i++;
	}
}
