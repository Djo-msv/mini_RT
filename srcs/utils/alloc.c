#include "miniRT.h"

void	free_thread(t_thread *thread)
{
	t_thread	*to_kill;

	if (!thread)
		return ;
	while (thread->next)
	{
		to_kill = thread;
		thread = thread->next;
		pthread_rwlock_destroy(to_kill->run_mutex);
		free(to_kill);
	}
}

void	free_data(t_data *data)
{
	free(data->image.new_img);
	free(data->image.old_img);
	free(data->image.mlx_img);
	free_thread(data->thread);
	ft_free_2d_tab((void **)data->setting_cam.ray_direction);
	ft_lstclear(&data->scene.light, free);
	ft_lstclear(&data->scene.cylinder, free);
	ft_lstclear(&data->scene.plane, free);
	ft_lstclear(&data->scene.sphere, free);
}
