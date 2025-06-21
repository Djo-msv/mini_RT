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

t_thread	*create_node(t_data *data, int id)
{
	t_thread	*node;

	(void)data;
	node = malloc(sizeof(t_thread));
	if (!node)
		return (NULL);
	node->id = id;
	node->run_mutex = malloc(sizeof(pthread_rwlock_t));
	if (node->run_mutex)
		pthread_rwlock_init(node->run_mutex, NULL);
	node->x_min = 0;
	node->x_max = 0;
	node->y_min = 0;
	node->y_max = 0;
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
