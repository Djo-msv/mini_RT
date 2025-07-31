/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:31:55 by star              #+#    #+#             */
/*   Updated: 2025/07/31 20:46:02 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	plane(t_hit h)
{
	int	checker;

	if (((t_plane *)h.obj)->is_pattern)
	{
		checker = ((int)floor(h.position.x / ((t_plane *)h.obj)->l_x_pattern)
				+ (int)floor(h.position.z
					/ ((t_plane *)h.obj)->l_x_pattern)) % 2;
		if (checker)
			h.color = mlxcolor_to_fcolor(((t_plane *)h.obj)->color);
		else
			h.color = mlxcolor_to_fcolor(((t_plane *)h.obj)->pattern_color);
	}
	else
		h.color = mlxcolor_to_fcolor(((t_plane *)h.obj)->color);
	h.normal = normalize(((t_plane *)h.obj)->normal);
	h.material = ((t_plane *)h.obj)->mat;
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
