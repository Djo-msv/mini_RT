/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:42:45 by star              #+#    #+#             */
/*   Updated: 2025/07/31 19:13:39 by star             ###   ########.fr       */
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

void	rotate_obj_x(t_hit select, int is_left)
{
	t_matrix	r_x;

	if (!is_left)
		r_x = mat4_rotation_x(0.01);
	else
		r_x = mat4_rotation_x(-0.01);
	if (select.type == 0)
		((t_plane *)select.obj)->normal = normalize(mul_mat4_to_vec(r_x,
					((t_plane *)select.obj)->normal, 0));
	else if (select.type == 2)
		((t_cylinder *)select.obj)->normal = normalize(mul_mat4_to_vec(r_x,
					((t_cylinder *)select.obj)->normal, 0));
	else if (select.type == 4)
		rotate_move_triangle((t_triangle *)select.obj, r_x, 1);
	else if (select.type == 5)
	{
		if (!is_left)
			((t_ellipsoid *)select.obj)->rotation.x += 0.01;
		else
			((t_ellipsoid *)select.obj)->rotation.x -= 0.01;
		init_elli_mat((t_ellipsoid *)select.obj);
	}
}

void	rotate_obj_z(t_hit select, int is_left)
{
	t_matrix	r_z;

	if (!is_left)
		r_z = mat4_rotation_z(0.01);
	else
		r_z = mat4_rotation_z(-0.01);
	if (select.type == 0)
		((t_plane *)select.obj)->normal = normalize(mul_mat4_to_vec(r_z,
					((t_plane *)select.obj)->normal, 0));
	else if (select.type == 2)
		((t_cylinder *)select.obj)->normal = normalize(mul_mat4_to_vec(r_z,
					((t_cylinder *)select.obj)->normal, 0));
	else if (select.type == 4)
		rotate_move_triangle((t_triangle *)select.obj, r_z, 1);
	else if (select.type == 5)
	{
		if (!is_left)
			((t_ellipsoid *)select.obj)->rotation.z += 0.01;
		else
			((t_ellipsoid *)select.obj)->rotation.z -= 0.01;
		init_elli_mat((t_ellipsoid *)select.obj);
	}
}

void	rotate_obj_y(t_hit select, int is_left)
{
	t_matrix	r_y;

	if (!is_left)
		r_y = mat4_rotation_y(0.01);
	else
		r_y = mat4_rotation_y(-0.01);
	if (select.type == 0)
		((t_plane *)select.obj)->normal = normalize(mul_mat4_to_vec(r_y,
					((t_plane *)select.obj)->normal, 0));
	else if (select.type == 2)
		((t_cylinder *)select.obj)->normal = normalize(mul_mat4_to_vec(r_y,
					((t_cylinder *)select.obj)->normal, 0));
	else if (select.type == 4)
		rotate_move_triangle((t_triangle *)select.obj, r_y, 1);
	else if (select.type == 5)
	{
		if (!is_left)
			((t_ellipsoid *)select.obj)->rotation.y += 0.01;
		else
			((t_ellipsoid *)select.obj)->rotation.y -= 0.01;
		init_elli_mat((t_ellipsoid *)select.obj);
	}
}
