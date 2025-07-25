/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:12:03 by star              #+#    #+#             */
/*   Updated: 2025/07/25 19:13:18 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float hit_cylinder(t_cylinder *cy, float rad, t_ray r)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t;
	t_vec	o_c;
	t_vec	d_perpendicular;
	t_vec	o_c_perpendicular;

	if (rad <= 0.01)
		cy->radius = 0.01;
	if (cy->height <= 0.01)
		cy->height = 0.01;
	o_c = vec_sub(r.origin, cy->coordinate);
	d_perpendicular = vec_sub(r.direction, vec_mul(cy->normal, scalar_product(r.direction, cy->normal)));
	o_c_perpendicular = vec_sub(o_c, vec_mul(cy->normal, scalar_product(o_c, cy->normal)));
	a = scalar_product(d_perpendicular, d_perpendicular);
	b = 2.0 * scalar_product(d_perpendicular, o_c_perpendicular);
	c = scalar_product(o_c_perpendicular, o_c_perpendicular) - rad * rad;
	delta = b * b - 4.0 * a * c;
	if (delta < 0.0)
		return (-1.0);
	else
		t = ((-b - sqrt(delta)) / (2.0 * a));
	o_c = vec_sub(vec_add(r.origin, vec_mul(r.direction, t)), cy->coordinate);
	float	height;
	height = scalar_product(o_c, cy->normal);
	if (height < -cy->height / 2.0 || height > cy->height / 2.0)
		return (-1.0);
	return (t);
}

float	hit_base_cylinder(t_cylinder *cy, t_vec center, t_ray r)
{
	float	t;

	t = hit_plane(center, cy->normal, r);
	if (t < 0.0)
		return (-1.0);
	if (length(vec_sub(vec_add(r.origin, vec_mul(r.direction, t)), center)) <= cy->radius)
		return (t);
	return (-1.0);
}
