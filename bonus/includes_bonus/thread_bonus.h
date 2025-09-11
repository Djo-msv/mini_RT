/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:01:11 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:23:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_BONUS_H
# define THREAD_BONUS_H

typedef struct s_thread_arg
{
	size_t		size;
	t_fcolor	*buffer_pnt;
	t_vec		*ray_direction;
	t_scene		*scene;
} t_thread_arg
__attribute__((aligned(64)));

typedef void (*thread_func_t)(t_thread_arg *);

typedef struct s_tpool_work
{
	thread_func_t			func;
	void			*arg;
	struct s_tpool_work		*next;
} t_tpool_work;

typedef struct s_tpool
{
	t_tpool_work	*work_first;
	t_tpool_work	*work_last;
	t_fcolor		*buffer_a;
	t_fcolor		*buffer_b;
	t_vec			*ray_direction;
	t_thread_arg	*arg;
	pthread_mutex_t	work_mutex;
	pthread_cond_t	work_cond;
	pthread_cond_t	working_cond;
	size_t			working_cnt;
	size_t			thread_cnt;
	bool			stop;
	bool			restart;
} t_tpool;

t_tpool	*tpool_create(size_t num);
void	tpool_wait(t_tpool *tm);
void	tpool_destroy(t_tpool *tm);
bool	tpool_add_work(t_tpool *tm, thread_func_t func, void *arg);
void	worker(void *arg);
int		lunch_thread(t_data *data);

void	swap_buffer(t_tpool *pool);
void	init_thread(t_data *data);
void	set_param(t_data *data);

#endif
