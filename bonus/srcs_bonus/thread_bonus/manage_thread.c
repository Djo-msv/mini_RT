/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmassavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:20:05 by jmassavi          #+#    #+#             */
/*   Updated: 2025/09/16 22:20:07 by jmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_tpool_work	*tpool_work_create(t_thread_func func, void *arg)
{
	t_tpool_work	*work;

	if (func == NULL)
		return (NULL);
	work = malloc(sizeof(*work));
	if (!work)
		return (NULL);
	work->func = func;
	work->arg = arg;
	work->next = NULL;
	return (work);
}

void	tpool_work_destroy(t_tpool_work *work)
{
	if (work == NULL)
		return ;
	free(work);
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
	free_pool(tm);
}

t_tpool_work	*tpool_work_get(t_tpool *tm)
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
		if (!tpool_add_work(tm, (t_thread_func)worker, arg++))
		{
			tpool_destroy(tm);
			return (1);
		}
	}
	return (0);
}
