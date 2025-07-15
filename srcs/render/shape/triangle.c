/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:02:01 by star              #+#    #+#             */
/*   Updated: 2025/07/08 16:30:16 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float hit_triangle(t_triangle *tr, t_ray r)
{
	t_vec   edge1;
	t_vec   edge2;
	t_vec	perpendicular_v;
	t_vec	s;
	t_vec	perpendicular_q;
	float	det;
	float	u;
	float	v;
	float	inv_det;
	float	t;

	edge1 = vec_sub(tr->b, tr->a);
	edge2 = vec_sub(tr->c, tr->a);
	perpendicular_v = cross(r.direction, edge2);
	det = scalar_product(edge1, perpendicular_v);
	if (fabs(det) <= 0.0)
		return (-1);
	inv_det = 1.0 / det;
	s = vec_sub(r.origin, tr->a);
	u = inv_det * scalar_product(s, perpendicular_v);
	if (u < 0.0 || u > 1.0)
		return (-1);
	perpendicular_q = cross(s, edge1);
	v = inv_det * scalar_product(r.direction, perpendicular_q);
	if (v < 0.0 || u + v > 1.0)
		return (-1);
	t = inv_det * scalar_product(edge2, perpendicular_q);
	if (t >= 0.0)
		return (t);
	return (-1.0);
}

t_vec	get_triangle_normal(t_triangle *t)
{
	return (normalize(cross(vec_sub(t->b, t->a), vec_sub(t->c, t->a))));
}