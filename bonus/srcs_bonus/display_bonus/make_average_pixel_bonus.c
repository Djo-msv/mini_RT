/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_average_pixel_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:38:42 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:28:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	c_sampling(double coef_new_p, double coef_old_p,
	t_fcolor *buf_img, t_fcolor *buf_thread)
{
	t_fcolor	rgb;

	rgb.r = fmin(fmax((*buf_thread).r * 255.0, 0.0), 255.0);
	rgb.g = fmin(fmax((*buf_thread).g * 255.0, 0.0), 255.0);
	rgb.b = fmin(fmax((*buf_thread).b * 255.0, 0.0), 255.0);
	(*buf_img).r = ((rgb.r * coef_old_p) + ((*buf_img).r * coef_new_p));
	(*buf_img).g = ((rgb.g * coef_old_p) + ((*buf_img).g * coef_new_p));
	(*buf_img).b = ((rgb.b * coef_old_p) + ((*buf_img).b * coef_new_p));
}

void	sampling(t_data *data)
{
	t_fcolor	*buf_img;
	t_fcolor	*buf_thread;
	int			y;
	int			x;

	buf_img = data->image.buf_img;
	buf_thread = data->pool->buffer_b;
	y = 0;
	while (y < data->mlx.info.height)
	{
		x = 0;
		while (x < data->mlx.info.width)
		{
			c_sampling(data->image.coef_new_p, data->image.coef_old_p,
				buf_img, buf_thread);
			buf_thread++;
			buf_img++;
			x++;
		}
		y++;
	}
}
