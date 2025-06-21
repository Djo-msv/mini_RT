#include "miniRT.h"

void	*rt_thread(void *list)
{
	t_thread	*thread;

	thread = (t_thread *)list;
//	char c = thread->id + '0';
	while (true)
	{
//		run image
		if (stop_rt(thread))
			break ;
	}
	return (NULL);
}
