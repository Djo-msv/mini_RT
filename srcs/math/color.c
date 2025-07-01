#include "miniRT.h"

t_fcolor add_color(t_fcolor c1, t_fcolor c2)
{
	return ((t_fcolor){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b});
}

t_fcolor scale_mlx_color(t_fcolor color, float factor)
{
    t_fcolor result;

    result.r = color.r * factor;
    result.g = color.g * factor;
    result.b = color.b * factor;
    return result;
}

t_fcolor scalar_color(t_fcolor c1, t_fcolor c2)
{
	return ((t_fcolor){c1.r * c2.r, c1.g * c2.g, c1.b * c2.b});
}


t_fcolor	mlxcolor_to_fcolor(mlx_color color)
{
	return ((t_fcolor){color.r / 255.0f, color.g / 255.0f, color.b / 255.0f});
}

void fcolor_to_mlxcolor(t_data *data, mlx_color *dst)
{
	int width = data->mlx.info.width;
	t_thread *thread = data->thread;

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

				dst[global_index].r = buffer_copy[local_index].r * 255.0f;
				dst[global_index].g = buffer_copy[local_index].g * 255.0f;
				dst[global_index].b = buffer_copy[local_index].b * 255.0f;
				dst[global_index].a = 255;
			}
		}
		atomic_store_explicit(thread->ready, false, memory_order_release);
		thread = thread->next;
	}
}
