/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:31:55 by star              #+#    #+#             */
/*   Updated: 2025/10/08 15:05:30 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_fcolor	checkboard(t_plane *p, t_hit h)
{
	int			checker;
	t_vec		u;
	t_vec		v;
	t_vec		c;
	float		uv_c[2];

	if (fabsf(p->normal.y) < 0.999)
		u = (t_vec){1, 0, 0};
	else
		u = (t_vec){0, 0, 1};
	c = vec_sub(h.position, p->coordinate);
	u = normalize(cross(u, p->normal));
	v = normalize(cross(p->normal, u));
	uv_c[0] = scalar_product(c, u);
	uv_c[1] = scalar_product(c, v);
	checker = ((int)floor(uv_c[0] / p->l_z_pattern)
			+ (int)floor(uv_c[1] / p->l_x_pattern)) % 2;
	if (checker)
		h.color = mlxcolor_to_fcolor(p->color);
	else
		h.color = mlxcolor_to_fcolor(p->pattern_color);
	return (h.color);
}

t_hit	plane(t_hit h)
{
	t_plane		*p;

	p = ((t_plane *)h.obj);
	if (p->is_pattern)
		h.color = checkboard(p, h);
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
	if (s->tex.is_texture || s->tex.is_normal)
		generate_uv(&x, &y, hit);
	if (s->tex.is_texture)
		hit.color = c_texture(x, y, hit, scene);
	else
		hit.color = mlxcolor_to_fcolor(s->color);
	if (s->tex.is_normal)
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
