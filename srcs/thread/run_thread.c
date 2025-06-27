#include "miniRT.h"

void	lock_all_mutex(t_thread *thread)
{
	while (thread)
	{
		if  (pthread_rwlock_wrlock(thread->data_mutex))
			printf("hello\n");
		thread = thread->next;
	}
}

void	unlock_all_mutex(t_thread *thread)
{
	while (thread)
	{
		pthread_rwlock_unlock(thread->data_mutex);
		thread = thread->next;
	}
}

void	thread_ray_direction(t_data *data, t_thread *thread)
{
	int		x = 0;
	int		y;
	t_vec	pixel_center;

	while (x != thread->x)
	{
		y = 0;
		while (y != thread->y_max - thread->y_min)
		{
			pixel_center = vec_add(
    			vec_add(data->setting_cam.pixel00_loc, vec_mul(data->setting_cam.pixel_delta_h, x)),
    			vec_mul(data->setting_cam.pixel_delta_v, y + thread->y_min));
			printf("%d - %d\n", x, y);
			thread->ray_direction[x][y] = vec_sub(pixel_center, data->setting_cam.camera_center);
//			if (y == 0 && thread->id == 0)
//				printf("%d (%f, %f, %f)\n", x, thread->ray_direction[x][y].x , thread->ray_direction[y][x].y, thread->ray_direction[y][x].z);
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
	int			ratio = data->mlx.info.height / NB_THREAD;
	t_thread 	*thread = data->thread;

	printf("\033[2J");
	printf("\033[H");
	lock_all_mutex(data->thread);
	while (thread)
	{
		thread->y_min = ratio * thread->id;
		if (thread->next)
			thread->y_max = (ratio * (thread->id + 1)) - 1;
		else
			thread->y_max = data->mlx.info.height;
		thread->x = data->mlx.info.width;
		printf("thread %d, %d - %d\n", thread->id, thread->y_min, thread->y_max);
		thread_ray_direction(data, thread);
		thread = thread->next;
	}
	unlock_all_mutex(data->thread);
}

void	handle_pixel(t_thread *thread, int x, int y, int resolution)
{
	int pos = y * thread->x + x;

//	if (thread->id == 0)
//		printf("%d - %d\n", thread->y_min, 0);
	if (y == 0 || x == 0 || y == thread->y_max - thread->y_min || x == thread->x)
		thread->buffer_a[pos] = (t_fcolor){0.0f, 0.0f, 1.0f};
	else
		render(thread->data, &thread->buffer_a[pos], thread->ray_direction[x][y]);
//	if (resolution != 1)
//		handle_low_resolution(thread->data, x, y, resolution);
//	t_vec	**ray = thread->ray_direction;
//	(void)ray;
	(void)resolution;
}

void	swap_buffer(t_thread **thread)
{
	t_fcolor	*buffer;

	pthread_mutex_lock((*thread)->buffer_mutex);
	buffer = (*thread)->buffer_a;
	(*thread)->buffer_a = (*thread)->buffer_b;
	(*thread)->buffer_b = buffer;
	pthread_mutex_unlock((*thread)->buffer_mutex);
}

void	select_pixel(t_thread *thread)
{
	int	x = 0;
	int	y;

	pthread_rwlock_rdlock(thread->data_mutex);
	while (x <= thread->x)
	{
		y = thread->y_min;
		while (y <= thread->y_max)
		{
			printf("%d - %d\n", x, y);
			handle_pixel(thread, x, y - thread->y_min, 1);
			y += 1;
		}
		x += 1;
	}
	swap_buffer(&thread);
	pthread_rwlock_unlock(thread->data_mutex);
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
