#ifndef THREAD_H
# define THREAD_H

typedef struct s_thread
{
	int			id;
	bool		is_set;
	bool		run;

	t_fcolor	*buffer_a;
	t_fcolor	*buffer_b;
	t_vec		*ray_direction;
	unsigned int	local_generation;
	int			y_min;
	int			y_max;
	int			x;

	t_data		*data;
	pthread_t	thread_t;
	pthread_rwlock_t	*run_mutex;
	pthread_rwlock_t	*data_mutex;
	atomic_bool			*should_break;
	atomic_bool			*ready;
	struct s_thread	*next;
}	t_thread;

int		init_thread(t_data *data);
int		stop_rt(t_thread *thread);
void	*rt_thread(void *list);
void	kill_thread(t_thread *thread);
void	change_thread_setting(t_data *data);
void	threads_ray_direction(t_data *data);

void	lock_all_mutex(t_thread *thread);
void	unlock_all_mutex(t_thread *thread);

#endif
