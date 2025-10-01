/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:31:55 by star              #+#    #+#             */
/*   Updated: 2025/10/01 16:38:24 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_hit	plane(t_hit h)
{
	int			checker;
	// t_matrix	r;
	t_matrix	r_inv;
	t_plane		*p;
	t_vec		local;

	p = ((t_plane *)h.obj);
	if (p->is_pattern)
	{
		// r = mul_mat4(mat4_rotation_x(p->normal.x), mul_mat4(mat4_rotation_y(p->normal.y), mat4_rotation_z(p->normal.z)));
		// r_inv = mat4_transpose(r);
		// local = mul_mat4_to_vec(r_inv, h.position, 1);

		// 	t_matrix	tr;
		// t_matrix	s;
		// t_matrix	r;
		// t_matrix	s_inv;
		t_matrix	t_inv;
		// t_matrix	tran;
		t_matrix	t_inv_t;

		// tr = mat4_translation(p->coordinate.x, p->coordinate.y, p->coordinate.z);
		// s = mat4_scale(1, 1, 1);
		// r = mul_mat4(mul_mat4(mat4_rotation_z(p->normal.z),
		// 			mat4_rotation_y(p->normal.y)),
		// 		mat4_rotation_x(p->normal.x));
		// tran = mul_mat4(tr, mul_mat4(r, s));
		r_inv = mul_mat4(mat4_rotation_x(-p->normal.x),
				mul_mat4(mat4_rotation_y(-p->normal.y),
					mat4_rotation_z(-p->normal.z)));
		t_inv = mul_mat4(r_inv, mat4_translation(-p->coordinate.x,
						-p->coordinate.y, -p->coordinate.z));
		t_inv_t = mul_mat4(mat4_transpose(r_inv), mat4_transpose(t_inv));
		local = normalize(mul_mat4_to_vec(t_inv_t, h.position, 0));
		checker = ((int)floor(local.x / p->l_x_pattern)
				+ (int)floor(local.z / p->l_z_pattern)) % 2;
		if (checker)
			h.color = mlxcolor_to_fcolor(p->color);
		else
			h.color = mlxcolor_to_fcolor(p->pattern_color);
	}
	else
		h.color = mlxcolor_to_fcolor(p->color);
	h.material = p->mat;
	return (h);
}

t_hit	sphere(t_scene scene, t_hit hit)
{
	t_sphere	*s;
	int			x;
	int			y;

	x = 0;
	y = 0;
	s = ((t_sphere *)hit.obj);
	if (s->tex.is_texture)
		hit.color = c_texture(&x, &y, hit, scene);
	else
		hit.color = mlxcolor_to_fcolor(s->color);
	hit.normal = bump_map(scene, hit, x, y);
	hit.material = s->mat;
	return (hit);
}

t_hit	cylinder(t_hit hit)
{
	t_vec	o_c;
	t_vec	projection;
	float	lenght;

	if (hit.part == 1)
	{
		o_c = vec_sub(hit.position, ((t_cylinder *)hit.obj)->coordinate);
		lenght = scalar_product(o_c, ((t_cylinder *)hit.obj)->normal);
		projection = vec_add(((t_cylinder *)hit.obj)->coordinate,
				vec_mul(((t_cylinder *)hit.obj)->normal, lenght));
		hit.normal = normalize(vec_sub(hit.position, projection));
	}
	else if (hit.part == 2)
		hit.normal = normalize(((t_cylinder *)hit.obj)->normal);
	else
		hit.normal = vec_mul(((t_cylinder *)hit.obj)->normal, -1);
	hit.color = mlxcolor_to_fcolor(((t_cylinder *)hit.obj)->color);
	hit.material = ((t_cylinder *)hit.obj)->mat;
	return (hit);
}

t_hit	ellipsoid(t_hit hit)
{
	hit.color = mlxcolor_to_fcolor(((t_ellipsoid *)hit.obj)->color);
	hit.material = ((t_ellipsoid *)hit.obj)->mat;
	return (hit);
}
