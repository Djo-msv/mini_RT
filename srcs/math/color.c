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
    int width = data->setting_cam.width;
    t_thread *thread = data->thread;

    while (thread)
    {
        int y_local;
        for (y_local = 0; y_local < (thread->y_max - thread->y_min); y_local++)
        {
            int y_global = thread->y_min + y_local;
            for (int x = 0; x < width; x++)
            {
                int local_index = y_local * width + x;
                int global_index = y_global * width + x;

                dst[global_index].r = thread->buffer_b[local_index].r * 255.0f;
                dst[global_index].g = thread->buffer_b[local_index].g * 255.0f;
                dst[global_index].b = thread->buffer_b[local_index].b * 255.0f;
                dst[global_index].a = 255;
            }
        }
        thread = thread->next;
    }
}
