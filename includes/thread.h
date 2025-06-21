#ifndef THREAD_H
# define THREAD_H

typedef struct s_thread
{
	int			id;
	bool		is_set;
	bool		run;
	atomic_bool	should_break;

	t_fcolor	*buffer_a;
	t_fcolor	*buffer_b;
	t_vec		**ray_direction;
	int			y_min;
	int			y_max;
	int			x;

	pthread_t	thread_t;
	pthread_rwlock_t	*run_mutex;

	struct s_thread	*next;
}	t_thread;

int		init_thread(t_data *data);
int		stop_rt(t_thread *thread);
void	*rt_thread(void *list);
void	kill_thread(t_thread *thread);
void	change_thread_setting(t_data *data);

#endif
