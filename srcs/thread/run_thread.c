/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:37:52 by star              #+#    #+#             */
/*   Updated: 2025/07/31 20:24:39 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_tpool_work	*tpool_work_create(thread_func_t func, void *arg)
{
	t_tpool_work	*work;

	if (func == NULL)
		return (NULL);
	work = malloc(sizeof(*work));
	work->func = func;
	work->arg = arg;
	work->next = NULL;
	return (work);
}

static void	tpool_work_destroy(t_tpool_work *work)
{
	if (work == NULL)
		return ;
	free(work);
}

static t_tpool_work	*tpool_work_get(t_tpool *tm)
{
	t_tpool_work	*work;

	if (tm == NULL)
		return (NULL);
	work = tm->work_first;
	if (work == NULL)
		return (NULL);
	if (work->next == NULL)
	{
		tm->work_first = NULL;
		tm->work_last = NULL;
	}
	else
		tm->work_first = work->next;
	return (work);
}

static void	*tpool_worker(void *arg)
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

t_tpool	*tpool_create(size_t num)
{
	t_tpool		*tm;
	pthread_t	thread;
	size_t		i;

	i = -1;
	if (num == 0)
		num = 2;
	tm = calloc(2, sizeof(*tm));
	tm->thread_cnt = num;
	tm->buffer_a = malloc((MAX_RES_H * MAX_RES_W) * sizeof(t_fcolor));
	tm->buffer_b = malloc((MAX_RES_H * MAX_RES_W) * sizeof(t_fcolor));
	tm->ray_direction = malloc(MAX_RES_H * MAX_RES_W * sizeof(t_vec));
	tm->arg = malloc(((MAX_RES_H * MAX_RES_W) / SIZE_CHUNK + 1)
			* sizeof(t_thread_arg));
	tm->restart = 1;
	pthread_mutex_init(&(tm->work_mutex), NULL);
	pthread_cond_init(&(tm->work_cond), NULL);
	pthread_cond_init(&(tm->working_cond), NULL);
	tm->work_first = NULL;
	tm->work_last = NULL;
	while (++i < num)
	{
		pthread_create(&thread, NULL, tpool_worker, tm);
		pthread_detach(thread);
	}
	return (tm);
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

void	tpool_destroy(t_tpool *tm)
{
	t_tpool_work	*work;
	t_tpool_work	*work2;

	if (tm == NULL)
		return ;
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
	free(tm->buffer_a);
	free(tm->buffer_b);
	free(tm->ray_direction);
	free(tm->arg);
	free(tm);
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
		tpool_add_work(tm, (thread_func_t)worker, arg++);
	}
	return (0);
}
