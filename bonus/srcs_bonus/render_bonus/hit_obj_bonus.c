/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:31:55 by star              #+#    #+#             */
/*   Updated: 2025/10/01 20:17:39 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_hit	plane(t_hit h)
{
	int			checker;
	t_plane		*p;
	t_vec		u;
	t_vec		v;
	t_vec		c;
	float		u_c;
	float		u_v;

	p = ((t_plane *)h.obj);
	if (p->is_pattern)
	{
		if (fabsf(p->normal.y) < 0.999)
			u = (t_vec) {1, 0, 0};
		else
			u = (t_vec) {0, 0, 1};
		u = normalize(cross(u, p->normal));
		v = normalize(cross(p->normal, u));
		c = vec_sub(h.position, p->coordinate);
		u_c = scalar_product(c, u);
		u_v = scalar_product(c, v);
		checker = ((int)floor(u_c / p->l_z_pattern)
				+ (int)floor(u_v / p->l_x_pattern)) % 2;
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
