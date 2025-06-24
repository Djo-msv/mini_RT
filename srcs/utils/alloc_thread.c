#include "miniRT.h"

void	calculate_thread_buffer(t_data *data)
{
	t_thread	*thread = data->thread;

	while (thread->next)
	{
		atomic_store(&thread->should_break, true);
		thread = thread->next;
	}
}

void	alloc_thread_ray(t_thread *thread)
{
	int		x;

	x = 0;
	thread->ray_direction = malloc((MAX_RES_H + 1) * sizeof(t_vec *));
	thread->ray_direction[MAX_RES_H] = 0;
	while (x != ((MAX_RES_V / NB_THREAD) + NB_THREAD))
	{
		thread->ray_direction[x] = malloc((MAX_RES_V / NB_THREAD) + NB_THREAD  * sizeof(t_vec));
		x++;
	}
}

t_thread	*create_node(t_data *data, int id)
{
	t_thread	*node;

	int			ratio = data->mlx.info.height / NB_THREAD;
	node = malloc(sizeof(t_thread));
	if (!node)
		return (NULL);
	node->id = id;
	node->buffer_a = malloc((((MAX_RES_V / NB_THREAD) + NB_THREAD) * MAX_RES_H) * sizeof(t_fcolor));
	node->buffer_b = malloc((((MAX_RES_V / NB_THREAD) + NB_THREAD) * MAX_RES_H) * sizeof(t_fcolor));
	node->run_mutex = malloc(sizeof(pthread_rwlock_t));
	if (node->run_mutex)
		pthread_rwlock_init(node->run_mutex, NULL);
	node->data_mutex = malloc(sizeof(pthread_rwlock_t));
	if (node->data_mutex)
		pthread_rwlock_init(node->data_mutex, NULL);
	node->buffer_mutex = malloc(sizeof(pthread_mutex_t));
	if (node->run_mutex)
		pthread_mutex_init(node->buffer_mutex, NULL);
	alloc_thread_ray(node);
	node->y_min = ratio * node->id;
	if (node->next)
		node->y_max = (ratio * (node->id + 1)) - 1;
	else
		node->y_max = data->mlx.info.height;
	node->x = data->mlx.info.width;
	node->run = true;
	node->should_break = false;
	node->next = NULL;
	node->thread_t = 0;
	return (node);
}

void	protect_node(t_data *data, t_thread **node, int id)
{
	*node = create_node(data, id);
	if (!(*node) || !(*node)->run_mutex )
	{
		free_data(data);
		exit(1);
	}
}

void	new_node(t_data *data, t_thread **head, int id)
{
	t_thread	*list;

	list = *head;
	if (!list)
	{
		protect_node(data, head, id);
		return ;
	}
	while (list->next)
		list = list->next;
	protect_node(data, &list->next, id);
}

void	alloc_thread(t_data *data)
{
	int		i;
	t_thread	*chained_list;

	i = 0;
	chained_list = NULL;
	while (i != NB_THREAD)
	{
		printf("%d\n", i);
		new_node(data, &chained_list, i++);
	}
	data->thread = chained_list;
}
