/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:33:53 by star              #+#    #+#             */
/*   Updated: 2025/09/09 17:33:45 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	resize(t_data *d, t_hit select, int is_min)
{
	float	s;

	if (!is_min)
		s = -0.05;
	else
		s = 0.05;
	if (select.type == 1)
	{
		((t_sphere *)select.obj)->radius += s;
		if (((t_sphere *)select.obj)->radius <= 0.05)
			((t_sphere *)select.obj)->radius = 0.05;
	}
	else if (select.type == 2)
		((t_cylinder *)select.obj)->radius += s;
	else if (select.type == 5)
		((t_ellipsoid *)select.obj)->size += s;
	d->image.nb_images = 0;
}

void	resize_obj(t_data *d, t_hit select)
{
	if (d->input.minus_button)
		resize(d, select, 0);
	if (d->input.plus_button)
		resize(d, select, 1);
	if (d->input.nine_button)
	{
		if (select.type == 2)
			((t_cylinder *)select.obj)->height += 0.05;
	}
	if (d->input.zero_button)
	{
		if (select.type == 2)
			((t_cylinder *)select.obj)->height -= 0.05;
	}
	d->image.nb_images = 0;
}
