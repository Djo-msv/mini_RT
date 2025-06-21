#include "miniRT.h"

void	thread_ray_direction(t_data *data, t_thread *thread)
{
	int		x;
	int		y = thread->y_min;
	t_vec	pixel_center;

	x = 0;
	while (y != thread->y_max)
	{
		while (x != data->setting_cam.width)
		{
			pixel_center = vec_add(
    			vec_add(data->setting_cam.pixel00_loc, vec_mul(data->setting_cam.pixel_delta_h, x)),
    			vec_mul(data->setting_cam.pixel_delta_v, y));
			thread->ray_direction[x][y] = vec_sub(pixel_center, data->setting_cam.camera_center);
			y++;
		}
		x++;
	}
}

void	threads_ray_direction(t_data *data)
{
	t_thread	*thread = data->thread;

	while (thread)
	{
		thread_ray_direction(data, thread);
		thread = thread->next;
	}
}

void	change_thread_setting(t_data *data)
{
	int			ratio = data->setting_cam.height / NB_THREAD;
	t_thread 	*thread = data->thread;

	while (thread)
	{
		thread->y_min = ratio * thread->id;
		if (thread->next)
			thread->y_max = (ratio * (thread->id + 1)) - 1;
		else
			thread->y_max = data->setting_cam.height;
		thread->x = data->setting_cam.width;
		printf("thread %d, %d - %d\n", thread->id, thread->y_min, thread->y_max);
		thread = thread->next;
	}
}
/*
	while (y < info.height)
	{
		x = 0;
		while (x < info.width)
		{
			handle_pixel(data, x, y, resolution);
			x += resolution;
		}
		y += resolution;
	}
*/
void	*rt_thread(void *list)
{
	t_thread	*thread;

	thread = (t_thread *)list;
	while (true)
	{
//		run
		if (stop_rt(thread))
			break ;
	}
	return (NULL);
}
