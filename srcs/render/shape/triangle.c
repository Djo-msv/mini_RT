/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:02:01 by star              #+#    #+#             */
/*   Updated: 2025/07/31 20:25:46 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	hit_triangle(t_triangle *tr, t_ray r)
{
	t_hit_triangle	h;
	float			t;

	h.edge1 = vec_sub(tr->b, tr->a);
	h.edge2 = vec_sub(tr->c, tr->a);
	h.perpendicular_v = cross(r.direction, h.edge2);
	h.det = scalar_product(h.edge1, h.perpendicular_v);
	if (fabs(h.det) <= 0.0)
		return (-1);
	h.inv_det = 1.0 / h.det;
	h.s = vec_sub(r.origin, tr->a);
	h.u = h.inv_det * scalar_product(h.s, h.perpendicular_v);
	if (h.u < 0.0 || h.u > 1.0)
		return (-1);
	h.perpendicular_q = cross(h.s, h.edge1);
	h.v = h.inv_det * scalar_product(r.direction, h.perpendicular_q);
	if (h.v < 0.0 || h.u + h.v > 1.0)
		return (-1);
	t = h.inv_det * scalar_product(h.edge2, h.perpendicular_q);
	if (t >= 0.0)
		return (t);
	return (-1.0);
}

t_vec	get_triangle_normal(t_triangle *t)
{
	return (normalize(cross(vec_sub(t->b, t->a), vec_sub(t->c, t->a))));
}
