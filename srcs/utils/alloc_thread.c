#include "miniRT.h"

void	calculate_thread_buffer(t_data *data)
{
	t_thread	*thread = data->thread;

	while (thread->next)
	{
		atomic_store(thread->should_break, true);
		thread = thread->next;
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
	node->buffer_a = malloc((((MAX_RES_H / NB_THREAD) + NB_THREAD) * MAX_RES_W) * sizeof(t_fcolor));
	node->buffer_b = malloc((((MAX_RES_H / NB_THREAD) + NB_THREAD) * MAX_RES_W) * sizeof(t_fcolor));
	node->run_mutex = malloc(sizeof(pthread_rwlock_t));
	if (node->run_mutex)
		pthread_rwlock_init(node->run_mutex, NULL);
	node->data_mutex = malloc(sizeof(pthread_rwlock_t));
	if (node->data_mutex)
		pthread_rwlock_init(node->data_mutex, NULL);
	node->ray_direction = malloc(((MAX_RES_W + 1) * ((MAX_RES_H / NB_THREAD) + NB_THREAD)) * sizeof(t_vec));
	node->y_min = ratio * node->id;
	if (node->id + 1 != NB_THREAD)
		node->y_max = (ratio * (node->id + 1)) - 1;
	else
		node->y_max = data->mlx.info.height;
	node->x = data->mlx.info.width;
	node->run = true;
	node->should_break = false;
	node->ready = malloc(sizeof(atomic_bool));
	atomic_init(node->ready, false);
	node->next = NULL;
	node->thread_t = 0;
	node->local_generation = 0;
	node->data = data;
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
		new_node(data, &chained_list, i++);
	data->thread = chained_list;
}
