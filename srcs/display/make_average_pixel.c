/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_average_pixel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:38:42 by star              #+#    #+#             */
/*   Updated: 2025/07/31 20:48:00 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
/*
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
*/

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
	double		coef_new_p;
	double		coef_old_p;
	t_fcolor	*buf_img;
	t_fcolor	*buf_thread;
	int			y;
	int			x;

	coef_new_p = data->image.coef_new_p;
	coef_old_p = data->image.coef_old_p;
	buf_img = data->image.buf_img;
	buf_thread = data->pool->buffer_b;
	y = 0;
	while (y < data->mlx.info.height)
	{
		x = 0;
		while (x < data->mlx.info.width)
		{
			c_sampling(coef_new_p, coef_old_p, buf_img, buf_thread);
			buf_thread++;
			buf_img++;
			x++;
		}
		y++;
	}
}
