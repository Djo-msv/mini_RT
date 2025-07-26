/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:12:03 by star              #+#    #+#             */
/*   Updated: 2025/07/26 16:17:17 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	height(t_cylinder *cy, t_vec abc, t_ray r)
{
	float	delta;
	float	height;
	t_vec	o_c;
	float	t;

	delta = abc.y * abc.y - 4.0 * abc.x * abc.z;
	if (delta < 0.0)
		return (-1.0);
	else
		t = ((-abc.y - sqrt(delta)) / (2.0 * abc.x));
	o_c = vec_sub(vec_add(r.origin, vec_mul(r.direction, t)), cy->coordinate);
	height = scalar_product(o_c, cy->normal);
	if (height < -cy->height / 2.0 || height > cy->height / 2.0)
		return (-1.0);
	return (t);
}

float	hit_cylinder(t_cylinder *cy, float rad, t_ray r)
{
	t_vec	abc;
	t_vec	o_c;
	t_vec	d_perpendicular;
	t_vec	o_c_perpendicular;

	if (rad <= 0.01)
		cy->radius = 0.01;
	if (cy->height <= 0.01)
		cy->height = 0.01;
	o_c = vec_sub(r.origin, cy->coordinate);
	d_perpendicular = vec_sub(r.direction, vec_mul(cy->normal,
				scalar_product(r.direction, cy->normal)));
	o_c_perpendicular = vec_sub(o_c, vec_mul(cy->normal,
				scalar_product(o_c, cy->normal)));
	abc.x = scalar_product(d_perpendicular, d_perpendicular);
	abc.y = 2.0 * scalar_product(d_perpendicular, o_c_perpendicular);
	abc.z = scalar_product(o_c_perpendicular, o_c_perpendicular) - rad * rad;
	return (height(cy, abc, r));
}

float	hit_base_cylinder(t_cylinder *cy, t_vec center, t_ray r)
{
	float	t;

	t = hit_plane(center, cy->normal, r);
	if (t < 0.0)
		return (-1.0);
	if (length(vec_sub(vec_add(r.origin, vec_mul(r.direction, t)),
				center)) <= cy->radius)
		return (t);
	return (-1.0);
}
