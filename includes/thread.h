#ifndef THREAD_H
# define THREAD_H

typedef struct s_thread
{
	int			id;
	bool		is_set;
	bool		run;
	t_fcolor	*buffer;
	int			x_min;
	int			x_max;
	int			y_min;
	int			y_max;

	pthread_t	thread_t;
	pthread_rwlock_t	*run_mutex;

	struct s_thread	*next;
}	t_thread;

int		init_thread(t_data *data);
int		stop_rt(t_thread *thread);
void	*rt_thread(void *list);

#endif
