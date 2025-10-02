/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:01:11 by star              #+#    #+#             */
/*   Updated: 2025/09/17 18:44:14 by star             ###   ########.fr       */
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
}	t_thread_arg
__attribute__((aligned(64)));

typedef void	(*t_thread_func)(t_thread_arg *);

typedef struct s_tpool_work
{
	t_thread_func			func;
	void					*arg;
	struct s_tpool_work		*next;
}	t_tpool_work;

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
}	t_tpool;

t_tpool			*tpool_create(size_t num);
t_tpool_work	*tpool_work_create(t_thread_func func, void *arg);
t_tpool_work	*tpool_work_get(t_tpool *tm);
void			*tpool_worker(void *arg);
void			tpool_work_destroy(t_tpool_work *work);
void			tpool_wait(t_tpool *tm);
void			*tpool_destroy(t_tpool *tm);
void			*tpool_kill(t_tpool *tm);
void			*free_pool(t_tpool *tm);
bool			tpool_add_work(t_tpool *tm, t_thread_func func, void *arg);
void			worker(void *arg);
int				lunch_thread(t_data *data);

void			swap_buffer(t_tpool *pool);
int				init_thread(t_data *data);

#endif
