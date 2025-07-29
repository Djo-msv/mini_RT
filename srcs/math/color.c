/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:02:45 by star              #+#    #+#             */
/*   Updated: 2025/07/29 17:02:53 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_fcolor	add_color(t_fcolor c1, t_fcolor c2)
{
	return ((t_fcolor){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b});
}

t_fcolor	scale_mlx_color(t_fcolor color, float factor)
{
	t_fcolor	result;

	result.r = color.r * factor;
	result.g = color.g * factor;
	result.b = color.b * factor;
	return (result);
}

t_fcolor	scalar_color(t_fcolor c1, t_fcolor c2)
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

	t_fcolor *buffer_img = data->image.buf_img;
	for (int y = 0; y < data->mlx.info.height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int global_index = y * width + x;
//			printf("hello\n");
			dst[global_index].r = buffer_img[global_index].r;
			dst[global_index].g = buffer_img[global_index].g;
			dst[global_index].b = buffer_img[global_index].b;
			dst[global_index].a = 255;
		}
	}
}
