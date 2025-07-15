#include "miniRT.h"

int	stop_rt(t_thread *thread)
{
	while (atomic_load(thread->data->generation_id) % 2)
		usleep(100);
	if (thread->run == false)
		return (1);
	return (0);
}

void	join_thread(t_thread *thread)
{
	while (thread)
	{
		pthread_join(thread->thread_t, NULL);
		thread->is_set = false;
		thread = thread->next;
	}
}

void	kill_thread(t_thread *thread)
{
	atomic_fetch_add(thread->data->generation_id, 1);
	while (thread->next)
	{
		thread->run = false;
		pthread_rwlock_unlock(thread->run_mutex);
		thread = thread->next;
		pthread_rwlock_wrlock(thread->run_mutex);
	}
	thread->run = false;
	atomic_fetch_add(thread->data->generation_id, 1);
}

int	init_thread(t_data *data)
{
	t_thread	*thread;

	thread = data->thread;
	while (thread)
	{
		if (pthread_create(&thread->thread_t, NULL, rt_thread, thread))
		{
			kill_thread(data->thread);
			join_thread(data->thread);
			return (1);
		}
		thread->is_set = true;
		thread = thread->next;
	}
	return (0);
}
