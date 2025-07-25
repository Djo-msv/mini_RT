/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:02:47 by star              #+#    #+#             */
/*   Updated: 2025/07/25 19:13:14 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	hit_ellipsoid(t_ellipsoid *e, t_ray r, t_hit *hit)
{
	t_ray		new_r;

	if (e->size <= 0.01)
		e->size = 0.01;
	new_r.origin = mul_mat4_to_vec(e->t_inv, r.origin, 1);
	new_r.direction = normalize(mul_mat4_to_vec(e->t_inv, r.direction, 0));
	float	t = hit_sphere((t_vec){0, 0, 0}, e->size, new_r);
	if (t < 0)
		return (-1);
	t_vec	local = vec_add(new_r.origin, vec_scale(new_r.direction, t));
	t_vec	n_local = normalize(local);
	hit->position = mul_mat4_to_vec(e->tran, local, 1);
	hit->normal = normalize(mul_mat4_to_vec(e->t_inv_t, n_local, 0));
	hit->obj = e;
	hit->t = t;
	hit->type = 5;
	return (t);
}
