#include "miniRT.h"

void	*rt_thread(void *list)
{
	t_thread	*thread;

	thread = (t_thread *)list;
	while (true)
	{
//		run image
		sleep(1);
		printf("-> %d\n", thread->id);
		if (stop_rt(thread))
			break ;
	}
	return (NULL);
}
