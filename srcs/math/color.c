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

void	fcolor_to_mlxcolor(t_data *data, mlx_color *dst)
{
	int			x;
	int			y;
	int			z;

	t_thread	*thread = data->thread;

	while (thread)
	{
		y = thread->y_min * thread->x;
		x = thread->y_max * thread->x;
		z = y;
		while (y != x)
		{
			dst[y].r = thread->buffer_b[y - z].r * 255.0f;
    		dst[y].g = thread->buffer_b[y - z].g * 255.0f;
        	dst[y].b = thread->buffer_b[y - z].b * 255.0f;
			dst[y].a = 255;
			y++;
		}
		thread = thread->next;
	}
}
