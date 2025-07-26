/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:05:50 by star              #+#    #+#             */
/*   Updated: 2025/07/26 16:40:57 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_obj_x(t_data *d, t_hit select, int is_left)
{
	t_matrix		t_x;

	if (!is_left)
		t_x = mat4_translation(0.01, 0.0, 0.0);
	else
		t_x = mat4_translation(-0.01, 0.0, 0.0);
	if (select.type == 0)
		((t_plane *)select.obj)->coordinate = mul_mat4_to_vec(t_x,
				((t_plane *)select.obj)->coordinate, 1);
	else if (select.type == 1 || select.type == 3)
		((t_sphere *)select.obj)->coordinate = mul_mat4_to_vec(t_x,
				((t_sphere *)select.obj)->coordinate, 1);
	else if (select.type == 2)
		((t_cylinder *)select.obj)->coordinate = mul_mat4_to_vec(t_x,
				((t_cylinder *)select.obj)->coordinate, 1);
	d->image.nb_images = 0;
}

void	move_obj_z(t_data *d, t_hit select, int is_forward)
{
	t_matrix		t_z;

	if (!is_forward)
		t_z = mat4_translation(0.0, 0.0, -0.01);
	else
		t_z = mat4_translation(0.0, 0.0, 0.01);
	if (select.type == 0)
		((t_plane *)select.obj)->coordinate = mul_mat4_to_vec(t_z,
				((t_plane *)select.obj)->coordinate, 1);
	else if (select.type == 1 || select.type == 3)
		((t_sphere *)select.obj)->coordinate = mul_mat4_to_vec(t_z,
				((t_sphere *)select.obj)->coordinate, 1);
	else if (select.type == 2)
		((t_cylinder *)select.obj)->coordinate = mul_mat4_to_vec(t_z,
				((t_cylinder *)select.obj)->coordinate, 1);
	d->image.nb_images = 0;
}

void	move_obj_y(t_data *d, t_hit select, int is_up)
{
	t_matrix		t_y;

	if (!is_up)
		t_y = mat4_translation(0.0, -0.01, 0.0);
	else
		t_y = mat4_translation(0.0, 0.01, 0.0);
	if (select.type == 0)
		((t_plane *)select.obj)->coordinate = mul_mat4_to_vec(t_y,
				((t_plane *)select.obj)->coordinate, 1);
	else if (select.type == 1 || select.type == 3)
		((t_sphere *)select.obj)->coordinate = mul_mat4_to_vec(t_y,
				((t_sphere *)select.obj)->coordinate, 1);
	else if (select.type == 2)
		((t_cylinder *)select.obj)->coordinate = mul_mat4_to_vec(t_y,
				((t_cylinder *)select.obj)->coordinate, 1);
	d->image.nb_images = 0;
}

static void	rotate(t_data *d, t_hit select, int key)
{
	if (key == 79)
		rotate_obj_x(d, select, 0);
	if (key == 80)
		rotate_obj_x(d, select, 1);
	if (key == 82)
		rotate_obj_y(d, select, 1);
	if (key == 81)
		rotate_obj_y(d, select, 0);
}

void	change_obj(t_data *d, t_hit select, int key)
{
	resize_obj(d, select, key);
	if (d->scene.select.rotate_mode)
		rotate(d, select, key);
	else
	{
		if (d->scene.select.up_mode)
		{
			if (key == 82)
				move_obj_y(d, select, 1);
			if (key == 81)
				move_obj_y(d, select, 0);
		}
		else
		{
			if (key == 79)
				move_obj_x(d, select, 0);
			if (key == 80)
				move_obj_x(d, select, 1);
			if (key == 82)
				move_obj_z(d, select, 1);
			if (key == 81)
				move_obj_z(d, select, 0);
		}
	}
}
