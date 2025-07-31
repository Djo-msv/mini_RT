/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:05:50 by star              #+#    #+#             */
/*   Updated: 2025/07/31 19:15:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	rotate(t_data *d, t_hit select)
{
	if (d->input.right_button)
		rotate_obj_x(select, 0);
	if (d->input.left_button)
		rotate_obj_x(select, 1);
	if (d->input.up_button)
		rotate_obj_y(select, 1);
	if (d->input.down_button)
		rotate_obj_y(select, 0);
}

static void	tr_moove(t_data *d, t_hit select)
{
	if (d->scene.select.up_mode)
	{
		if (d->input.up_button)
			move_obj_y(select, 1);
		if (d->input.down_button)
			move_obj_y(select, 0);
	}
	else
	{
		if (d->input.right_button)
			move_obj_x(select, 0);
		if (d->input.left_button)
			move_obj_x(select, 1);
		if (d->input.up_button)
			move_obj_z(select, 1);
		if (d->input.down_button)
			move_obj_z(select, 0);
	}
}

void	change_obj(t_data *d, t_hit select)
{
	resize_obj(d, select);
	if (d->scene.select.scale_mode && select.type == 5)
	{
		if (d->input.up_button)
			((t_ellipsoid *)select.obj)->scale.y += 0.01;
		if (d->input.down_button)
			((t_ellipsoid *)select.obj)->scale.y -= 0.01;
		if (d->input.right_button)
			((t_ellipsoid *)select.obj)->scale.z += 0.01;
		if (d->input.left_button)
			((t_ellipsoid *)select.obj)->scale.z -= 0.01;
		init_elli_mat((t_ellipsoid *)select.obj);
		d->image.nb_images = 0;
	}
	else if (d->scene.select.rotate_mode)
		rotate(d, select);
	else
		tr_moove(d, select);
	d->image.nb_images = 0;
}
