/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_obj_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:10:44 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:28:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	move_obj_x(t_hit select, int is_forward)
{
	t_matrix		t_x;

	if (is_forward)
		t_x = mat4_translation(0.05, 0.0, 0.0);
	else
		t_x = mat4_translation(-0.05, 0.0, 0.0);
	if (select.type == 0)
		((t_plane *)select.obj)->coordinate = mul_mat4_to_vec(t_x,
				((t_plane *)select.obj)->coordinate, 1);
	else if (select.type == 1 || select.type == 3)
		((t_sphere *)select.obj)->coordinate = mul_mat4_to_vec(t_x,
				((t_sphere *)select.obj)->coordinate, 1);
	else if (select.type == 4)
		rotate_move_triangle(((t_triangle *)select.obj), t_x, 0);
	else if (select.type == 2)
		((t_cylinder *)select.obj)->coordinate = mul_mat4_to_vec(t_x,
				((t_cylinder *)select.obj)->coordinate, 1);
	else if (select.type == 5)
	{
		((t_ellipsoid *)select.obj)->coordinate = mul_mat4_to_vec(t_x,
				((t_ellipsoid *)select.obj)->coordinate, 1);
		init_elli_mat((t_ellipsoid *)select.obj);
	}
}

void	move_obj_z(t_hit select, int is_left)
{
	t_matrix		t_z;

	if (is_left)
		t_z = mat4_translation(0.0, 0.0, -0.05);
	else
		t_z = mat4_translation(0.0, 0.0, 0.05);
	if (select.type == 0)
		((t_plane *)select.obj)->coordinate = mul_mat4_to_vec(t_z,
				((t_plane *)select.obj)->coordinate, 1);
	else if (select.type == 1 || select.type == 3)
		((t_sphere *)select.obj)->coordinate = mul_mat4_to_vec(t_z,
				((t_sphere *)select.obj)->coordinate, 1);
	else if (select.type == 4)
		rotate_move_triangle(((t_triangle *)select.obj), t_z, 0);
	else if (select.type == 2)
		((t_cylinder *)select.obj)->coordinate = mul_mat4_to_vec(t_z,
				((t_cylinder *)select.obj)->coordinate, 1);
	else if (select.type == 5)
	{
		((t_ellipsoid *)select.obj)->coordinate = mul_mat4_to_vec(t_z,
				((t_ellipsoid *)select.obj)->coordinate, 1);
		init_elli_mat((t_ellipsoid *)select.obj);
	}
}

void	move_obj_y(t_hit select, int is_up)
{
	t_matrix		t_y;

	if (!is_up)
		t_y = mat4_translation(0.0, -0.05, 0.0);
	else
		t_y = mat4_translation(0.0, 0.05, 0.0);
	if (select.type == 0)
		((t_plane *)select.obj)->coordinate = mul_mat4_to_vec(t_y,
				((t_plane *)select.obj)->coordinate, 1);
	else if (select.type == 1 || select.type == 3)
		((t_sphere *)select.obj)->coordinate = mul_mat4_to_vec(t_y,
				((t_sphere *)select.obj)->coordinate, 1);
	else if (select.type == 4)
		rotate_move_triangle(((t_triangle *)select.obj), t_y, 0);
	else if (select.type == 2)
		((t_cylinder *)select.obj)->coordinate = mul_mat4_to_vec(t_y,
				((t_cylinder *)select.obj)->coordinate, 1);
	else if (select.type == 5)
	{
		((t_ellipsoid *)select.obj)->coordinate = mul_mat4_to_vec(t_y,
				((t_ellipsoid *)select.obj)->coordinate, 1);
		init_elli_mat((t_ellipsoid *)select.obj);
	}
}
