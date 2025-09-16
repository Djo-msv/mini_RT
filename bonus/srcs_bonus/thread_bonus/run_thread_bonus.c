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

void	*tpool_worker(void *arg)
{
	t_tpool			*tm;
	t_tpool_work	*work;

	tm = arg;
	while (1)
	{
		pthread_mutex_lock(&(tm->work_mutex));
		while (tm->work_first == NULL && !tm->stop)
			pthread_cond_wait(&(tm->work_cond), &(tm->work_mutex));
		if (tm->stop)
			break ;
		work = tpool_work_get(tm);
		tm->working_cnt++;
		pthread_mutex_unlock(&(tm->work_mutex));
		if (work != NULL)
		{
			work->func(work->arg); //render
			tpool_work_destroy(work);
		}
		pthread_mutex_lock(&(tm->work_mutex));
		tm->working_cnt--;
		if (!tm->stop && tm->working_cnt == 0 && tm->work_first == NULL)
			pthread_cond_signal(&(tm->working_cond));
		pthread_mutex_unlock(&(tm->work_mutex));
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

bool	tpool_add_work(t_tpool *tm, thread_func_t func, void *arg)
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

int	lunch_thread(t_data *data)
{
	t_tpool			*tm;
	int				nb_chunk;
	t_thread_arg	*arg;
	int				i;

	i = -1;
	tm = data->pool;
	nb_chunk = data->param.nb_chunk;
	arg = tm->arg;
	while (++i < nb_chunk)
	{
		*arg = (t_thread_arg){SIZE_CHUNK, &(tm->buffer_a[i * SIZE_CHUNK]),
			&(tm->ray_direction[i * SIZE_CHUNK]), &data->scene};
		if (i == nb_chunk - 1)
			(*arg).size = (data->mlx.info.height * data->mlx.info.width)
				- ((nb_chunk - 1) * SIZE_CHUNK);
		if (!tpool_add_work(tm, (thread_func_t)worker, arg++))
		{
			tpool_destroy(tm);
			return (1);
		}
	}
	return (0);
}
