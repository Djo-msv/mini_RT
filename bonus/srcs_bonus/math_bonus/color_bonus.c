/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:02:45 by star              #+#    #+#             */
/*   Updated: 2025/10/01 19:21:14 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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

void	fcolor_to_mlxcolor(t_data *data, mlx_color *dst)
{
	t_fcolor	*buffer_img;
	int			width;
	int			y;
	int			x;
	int			global_index;

	width = data->mlx.info.width;
	buffer_img = data->image.buf_img;
	y = -1;
	while (++y < data->mlx.info.height)
	{
		x = -1;
		while (++x < width)
		{
			global_index = y * width + x;
			dst[global_index].r = buffer_img[global_index].r;
			dst[global_index].g = buffer_img[global_index].g;
			dst[global_index].b = buffer_img[global_index].b;
			dst[global_index].a = 255;
		}
	}
}
