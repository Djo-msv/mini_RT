#include "miniRT.h"

int	stop_rt(t_thread *thread)
{
	pthread_rwlock_rdlock(thread->run_mutex);
	if (thread->run == false)
	{
		pthread_rwlock_unlock(thread->run_mutex);
		return (1);
	}
	pthread_rwlock_unlock(thread->run_mutex);
	return (0);
}

void	join_thread(t_thread *thread)
{
	while (thread->is_set == true)
	{
		pthread_join(thread->thread_t, NULL);
		thread->is_set = false;
		thread = thread->next;
	}
}

void	kill_thread(t_thread *thread)
{
	pthread_rwlock_wrlock(thread->run_mutex);
	while (thread->next)
	{
		thread->run = true;
		pthread_rwlock_unlock(thread->run_mutex);
		thread = thread->next;
		pthread_rwlock_wrlock(thread->run_mutex);
	}
	pthread_rwlock_unlock(thread->run_mutex);
}

int	init_thread(t_data *data)
{
	t_thread	*thread;

	thread = data->thread;
	while (thread->next)
	{
		printf("thread id = %d\n", thread->id);
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
