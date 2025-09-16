/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_thread_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:37:57 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:28:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	init_thread(t_data *data)
{
	data->pool = tpool_create(NB_THREAD);
	if (!data->pool)
		return (1);
	return (0);
}

void	set_param(t_data *data)
{
	data->param.nb_chunk = ((data->mlx.info.height
				* data->mlx.info.width) / SIZE_CHUNK) + 1;
}

void	free_pool(t_tpool *tm)
{
	if (!tm)
		return;
	free(tm->buffer_a);
	free(tm->buffer_b);
	free(tm->ray_direction);
	free(tm->arg);
	free(tm);
	tm = NULL;
}

t_tpool	*safe_pool_alloc()
{
	t_tpool	*tm;

	tm = malloc(sizeof(*tm));
	if (!tm)
		return (NULL);
	tm->buffer_a = malloc((MAX_RES_H * MAX_RES_W) * sizeof(t_fcolor));
	tm->buffer_b = malloc((MAX_RES_H * MAX_RES_W) * sizeof(t_fcolor));
	tm->ray_direction = malloc(MAX_RES_H * MAX_RES_W * sizeof(t_vec));
	tm->arg = malloc(((MAX_RES_H * MAX_RES_W) / SIZE_CHUNK + 1)
			* sizeof(t_thread_arg));
	if (!tm->buffer_a || !tm->buffer_b || !tm->ray_direction || !tm->arg)
	{
		free_pool(tm);
		return (NULL);
	}
	return (tm);
}

t_tpool	*tpool_create(size_t num)
{
	t_tpool		*tm;
	pthread_t	thread;
	size_t		i;

	i = -1;
	if (num == 0)
		num = 2;
	tm = safe_pool_alloc();
	if (!tm)
		return (NULL);
	tm->thread_cnt = num;
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

void	swap_buffer(t_tpool *pool)
{
	t_fcolor	*tmp;

	tpool_wait(pool);
	tmp = pool->buffer_a;
	pool->buffer_a = pool->buffer_b;
	pool->buffer_b = tmp;
}
