#include "miniRT.h"

void	thread_ray_direction(t_data *data, t_thread *thread)
{
	int		x = 0;
	int		y = 0;
	t_vec	pixel_center;
	t_vec	*ray_direction = thread->ray_direction;

	while (y != thread->y_max - thread->y_min + 1)
	{
		x = 0;
		while (x != thread->x)
		{
			pixel_center = vec_add(
				vec_add(data->setting_cam.pixel00_loc, vec_mul(data->setting_cam.pixel_delta_h, x)),
				vec_mul(data->setting_cam.pixel_delta_v, y + thread->y_min));
			(*ray_direction) = vec_sub(pixel_center, data->setting_cam.camera_center);
			ray_direction++;
			x++;
		}
		y++;
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
	int			ratio = data->mlx.info.height / NB_THREAD;
	t_thread 	*thread = data->thread;

	while (thread)
	{
		thread->y_min = ratio * thread->id;
		if (thread->next)
			thread->y_max = (ratio * (thread->id + 1)) - 1;
		else
			thread->y_max = data->mlx.info.height;
		thread->x = data->mlx.info.width;
		thread_ray_direction(data, thread);
		thread = thread->next;
	}
}

void	swap_buffer(t_thread *thread)
{
	t_fcolor *buffer;

	while (atomic_load_explicit(thread->ready, memory_order_acquire))
		usleep(100);
	if (atomic_load(thread->data->generation_id) != thread->local_generation)
		return ;
	buffer = thread->buffer_a;
	thread->buffer_a = thread->buffer_b;
	thread->buffer_b = buffer;

	atomic_store_explicit(thread->ready, true, memory_order_release);
}

void	select_pixel(t_thread *thread)
{
	int	x = 0;
	int	y;
	int resolution = thread->data->image.resolution;
	t_vec	*ray_direction = thread->ray_direction;
	t_fcolor	*buf = thread->buffer_a;

	y = thread->y_min;
	while (y <= thread->y_max)
	{
		x = 0;
		while (x <= thread->x)
		{
			if (atomic_load(thread->data->generation_id) != thread->local_generation)
			{
				thread->local_generation += 2;
				atomic_store_explicit(thread->ready, false, memory_order_release);
				while (atomic_load(thread->data->generation_id) % 2)
					usleep(10);
//				thread->local_generation = atomic_load(thread->data->generation_id);
				return ;
			}
			render(thread->data, buf, *ray_direction);
//			if (resolution != 1)
//				handle_low_resolution(buf, x, y, resolution);
			buf++;
			ray_direction++;
			x += resolution;
		}
		y += resolution;
	}
	swap_buffer(thread);
}

void	*rt_thread(void *list)
{
	t_thread	*thread;

	thread = (t_thread *)list;
	while (true)
	{
		select_pixel(thread);
		if (stop_rt(thread))
			break ;
	}
	return (NULL);
}
