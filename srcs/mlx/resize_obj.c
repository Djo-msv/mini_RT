/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:33:53 by star              #+#    #+#             */
/*   Updated: 2025/07/31 18:44:27 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	resize(t_data *d, t_hit select, int is_min)
{
	float	s;

	if (!is_min)
		s = -0.01;
	else
		s = 0.01;
	if (select.type == 1)
	{
		((t_sphere *)select.obj)->radius += s;
		if (((t_sphere *)select.obj)->radius <= 0.01)
			((t_sphere *)select.obj)->radius = 0.01;
	}
	else if (select.type == 2)
		((t_cylinder *)select.obj)->radius += s;
	else if (select.type == 5)
		((t_ellipsoid *)select.obj)->size += s;
	d->image.nb_images = 0;
}

void	resize_obj(t_data *d, t_hit select, int key)
{
	if (d->input.minus_button)
		resize(d, select, 0);
	if (d->input.plus_button)
		resize(d, select, 1);
	if (key == 38)
	{
		if (select.type == 2)
			((t_cylinder *)select.obj)->height += 0.01;
		if (select.type == 5)
		{
			((t_ellipsoid *)select.obj)->scale.x += 0.01;
			init_elli_mat((t_ellipsoid *)select.obj);
		}
		d->image.nb_images = 0;
	}
	if (key == 39)
	{
		if (select.type == 2)
			((t_cylinder *)select.obj)->height -= 0.01;
		if (select.type == 5)
		{
			((t_ellipsoid *)select.obj)->scale.x -= 0.01;
			init_elli_mat((t_ellipsoid *)select.obj);
		}
		d->image.nb_images = 0;
	}
}
