/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:42:45 by star              #+#    #+#             */
/*   Updated: 2025/07/25 19:34:34 by star             ###   ########.fr       */
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
	d->image.nb_images = 0;
}

void	resize_obj(t_data *d, t_hit select, int key)
{
	if (key == 45)
		resize(d, select, 0);
	if (key == 46)
		resize(d, select, 1);
	if (key == 38)
	{
		if (select.type == 2)
			((t_cylinder *)select.obj)->height += 0.01;
		d->image.nb_images = 0;
	}
	if (key == 39)
	{
		if (select.type == 2)
			((t_cylinder *)select.obj)->height -= 0.01;
		d->image.nb_images = 0;
	}
}

void	rotate_obj_x(t_data *d, t_hit select, int is_left)
{
	t_matrix	r_x;

	if (!is_left)
		r_x = mat4_rotation_x(0.01);
	else
		r_x = mat4_rotation_x(-0.01);
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
	d->image.nb_images = 0;
}

void	rotate_obj_z(t_data *d, t_hit select, int is_left)
{
	t_matrix	r_z;

	if (!is_left)
		r_z = mat4_rotation_z(0.01);
	else
		r_z = mat4_rotation_z(-0.01);
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
	d->image.nb_images = 0;
}

void	rotate_obj_y(t_data *d, t_hit select, int is_left)
{
	t_matrix	r_y;

	if (!is_left)
		r_y = mat4_rotation_y(0.01);
	else
		r_y = mat4_rotation_y(-0.01);
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
	d->image.nb_images = 0;
}
