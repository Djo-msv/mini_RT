#include "miniRT.h"

void	average_pixel(t_fcolor *n_pixel, t_fcolor o_pixel, float coef_new_p, float coef_old_p)
{
	float	tmp;

	tmp = (n_pixel->r * coef_old_p) + (o_pixel.r * coef_new_p);
	n_pixel->r = tmp; 
	tmp = (n_pixel->g * coef_old_p) + (o_pixel.g * coef_new_p);
	n_pixel->g = tmp; 
	tmp = (n_pixel->b * coef_old_p) + (o_pixel.b * coef_new_p);
	n_pixel->b = tmp;
}

void	sampling(t_data *data)
{
	int width = data->mlx.info.width;
	double coef_new_p = data->image.coef_new_p;
	double coef_old_p = data->image.coef_old_p;
	t_thread *thread = data->thread;
	t_fcolor	*buf_img = data->image.buf_img;

	while (thread)
	{
		int y_local;

		while(!atomic_load_explicit(thread->ready, memory_order_acquire))
			usleep(100);
		t_fcolor *buffer_copy = thread->buffer_b;
		for (y_local = 0; y_local <= (thread->y_max - thread->y_min); y_local++)
		{
			int y_global = thread->y_min + y_local;
			for (int x = 0; x < width; x++)
			{
				int local_index = y_local * width + x;
				int global_index = y_global * width + x;

				double r = fmin(fmax(buffer_copy[local_index].r * 255.0, 0.0), 255.0);
				double g = fmin(fmax(buffer_copy[local_index].g * 255.0, 0.0), 255.0);
				double b = fmin(fmax(buffer_copy[local_index].b * 255.0, 0.0), 255.0);

				buf_img[global_index].r = ((r * coef_old_p) + (buf_img[global_index].r * coef_new_p));
				buf_img[global_index].g = ((g * coef_old_p) + (buf_img[global_index].g * coef_new_p));
				buf_img[global_index].b = ((b * coef_old_p) + (buf_img[global_index].b * coef_new_p));
			}
		}
		atomic_store_explicit(thread->ready, false, memory_order_release);
		thread = thread->next;
	}
}
