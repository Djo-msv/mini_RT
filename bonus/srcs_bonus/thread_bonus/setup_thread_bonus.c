/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_thread_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:37:57 by star              #+#    #+#             */
/*   Updated: 2025/10/06 16:44:14 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	init_thread(t_data *data)
{
	int	nb_t;

	if (NB_THREAD <= 2 || NB_THREAD > 172)
		nb_t = 2;
	else
		nb_t = NB_THREAD;
	data->pool = tpool_create(nb_t);
	if (!data->pool)
		return (1);
	return (0);
}

void	*free_pool(t_tpool *tm)
{
	if (!tm)
		return (NULL);
	free(tm->buffer_a);
	free(tm->buffer_b);
	free(tm->ray_direction);
	free(tm->arg);
	free(tm);
	tm = NULL;
	return (NULL);
}

t_tpool	*safe_pool_alloc(void)
{
	t_tpool	*tm;

	tm = ft_calloc(1, sizeof(*tm));
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
	tm = safe_pool_alloc();
	if (!tm)
		return (NULL);
	tm->thread_cnt = num;
	tm->restart = 1;
	if (pthread_mutex_init(&(tm->work_mutex), NULL) != 0
		|| pthread_cond_init(&(tm->work_cond), NULL) != 0
		|| pthread_cond_init(&(tm->working_cond), NULL) != 0)
		return (free_pool(tm));
	tm->work_first = NULL;
	tm->work_last = NULL;
	while (++i < num)
	{
		tm->thread_cnt = i + 1;
		if (pthread_create(&thread, NULL, tpool_worker, tm))
			return (tpool_kill(tm));
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
