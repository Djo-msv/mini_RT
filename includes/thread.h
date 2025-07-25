#ifndef THREAD_H
# define THREAD_H

typedef struct s_thread_arg
{
	size_t		size;
	t_fcolor	*buffer_pnt;
	t_vec		*ray_direction;
	t_scene		scene;
} t_thread_arg;

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

# define SIZE_CHUNK 4096

#endif
