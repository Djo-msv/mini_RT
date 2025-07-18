/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:05:50 by star              #+#    #+#             */
/*   Updated: 2025/07/08 17:45:13 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rotate_move_triangle(t_triangle *tr, t_matrix t, int is_rotate)
{
	tr->a = mul_mat4_to_vec(t, tr->a, 1);
	tr->b = mul_mat4_to_vec(t, tr->b, 1);
	tr->c = mul_mat4_to_vec(t, tr->c, 1);
	if (is_rotate)
		tr->normal = get_triangle_normal(tr);

}

void	rotate_obj_x(t_data *d, t_hit select, int is_left)
{
	t_matrix	r_x;

	if (!is_left)
		r_x = mat4_rotation_x(0.1);
	else
		r_x = mat4_rotation_x(-0.1);
	if (select.type == 0)
	{
		((t_plane *)select.obj)->normal = mul_mat4_to_vec(r_x, ((t_plane *)select.obj)->normal, 0);
		((t_plane *)select.obj)->normal = normalize(((t_plane *)select.obj)->normal);
	}
	else if (select.type == 2)
	{
		t_cylinder *c = (t_cylinder *)select.obj;
		c->normal = mul_mat4_to_vec(r_x, c->normal, 0);
		c->normal = normalize(c->normal);
	}
	else if (select.type == 4)
		rotate_move_triangle((t_triangle *)select.obj, r_x, 1);
	d->image.nb_images = 0;
}

void	rotate_obj_z(t_data *d, t_hit select, int is_left)
{
	t_matrix	r_z;

	if (!is_left)
		r_z = mat4_rotation_z(0.1);
	else
		r_z = mat4_rotation_z(-0.1);
	if (select.type == 0)
	{
		((t_plane *)select.obj)->normal = mul_mat4_to_vec(r_z, ((t_plane *)select.obj)->normal, 0);
		((t_plane *)select.obj)->normal = normalize(((t_plane *)select.obj)->normal);
	}
	else if (select.type == 2)
	{
		t_cylinder *c = (t_cylinder *)select.obj;
		c->normal = mul_mat4_to_vec(r_z, c->normal, 0);
		c->normal = normalize(c->normal);
	}
	else if (select.type == 4)
		rotate_move_triangle((t_triangle *)select.obj, r_z, 1);
	d->image.nb_images = 0;
}

void	rotate_obj_y(t_data *d, t_hit select, int is_left)
{
	t_matrix	r_y;

	if (!is_left)
		r_y = mat4_rotation_y(0.1);
	else
		r_y = mat4_rotation_y(-0.1);
	if (select.type == 0)
	{
		((t_plane *)select.obj)->normal = mul_mat4_to_vec(r_y, ((t_plane *)select.obj)->normal, 0);
		((t_plane *)select.obj)->normal = normalize(((t_plane *)select.obj)->normal);
	}
	else if (select.type == 2)
	{
		t_cylinder *c = (t_cylinder *)select.obj;
		c->normal = mul_mat4_to_vec(r_y, c->normal, 0);
		c->normal = normalize(c->normal);
	}
	else if (select.type == 4)
		rotate_move_triangle((t_triangle *)select.obj, r_y, 1);
	d->image.nb_images = 0;
}

void	move_obj_x(t_data *d, t_hit select, int is_left)
{
	t_matrix		t_x;

	if (!is_left)
		t_x = mat4_translation(0.1, 0.0, 0.0);
	else
		t_x = mat4_translation(-0.1, 0.0, 0.0);
	if (select.type == 0)
		((t_plane *)select.obj)->coordinate = mul_mat4_to_vec(t_x, ((t_plane *)select.obj)->coordinate, 1);
	else if (select.type == 1 || select.type == 3)
		((t_sphere *)select.obj)->coordinate = mul_mat4_to_vec(t_x, ((t_sphere *)select.obj)->coordinate, 1);
	else if (select.type == 4)
		rotate_move_triangle(((t_triangle *)select.obj), t_x, 0);
	else
		((t_cylinder *)select.obj)->coordinate = mul_mat4_to_vec(t_x, ((t_cylinder *)select.obj)->coordinate, 1);
	d->image.nb_images = 0;
}

void	move_obj_z(t_data *d, t_hit select, int is_forward)
{
	t_matrix		t_z;

	if (!is_forward)
		t_z = mat4_translation(0.0, 0.0, -0.1);
	else
		t_z = mat4_translation(0.0, 0.0, 0.1);
	if (select.type == 0)
		((t_plane *)select.obj)->coordinate = mul_mat4_to_vec(t_z, ((t_plane *)select.obj)->coordinate, 1);
	else if (select.type == 1 || select.type == 3)
		((t_sphere *)select.obj)->coordinate = mul_mat4_to_vec(t_z, ((t_sphere *)select.obj)->coordinate, 1);
	else if (select.type == 4)
		rotate_move_triangle(((t_triangle *)select.obj), t_z, 0);
	else
		((t_cylinder *)select.obj)->coordinate = mul_mat4_to_vec(t_z, ((t_cylinder *)select.obj)->coordinate, 1);
	d->image.nb_images = 0;
}

void	move_obj_y(t_data *d, t_hit select, int is_up)
{
	t_matrix		t_y;

	if (!is_up)
		t_y = mat4_translation(0.0, -0.1, 0.0);
	else
		t_y = mat4_translation(0.0, 0.1, 0.0);
	if (select.type == 0)
		((t_plane *)select.obj)->coordinate = mul_mat4_to_vec(t_y, ((t_plane *)select.obj)->coordinate, 1);
	else if (select.type == 1 || select.type == 3)
		((t_sphere *)select.obj)->coordinate = mul_mat4_to_vec(t_y, ((t_sphere *)select.obj)->coordinate, 1);
	else if (select.type == 4)
		rotate_move_triangle(((t_triangle *)select.obj), t_y, 0);
	else
		((t_cylinder *)select.obj)->coordinate = mul_mat4_to_vec(t_y, ((t_cylinder *)select.obj)->coordinate, 1);
	d->image.nb_images = 0;
}


void	change_obj(t_data *d, t_hit select, int key)
{
	if (d->scene.select.rotate_mode)
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
