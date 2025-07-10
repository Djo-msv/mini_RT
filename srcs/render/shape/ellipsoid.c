/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:02:47 by star              #+#    #+#             */
/*   Updated: 2025/07/10 20:28:55 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	hit_ellipsoid(t_ellipsoid *e, t_ray r)
{
	t_matrix	tr;
	t_matrix	ro;
	t_matrix	s;
	t_ray		new_r;

	tr = mat4_translation(e->coordinate.x, e->coordinate.y, e->coordinate.z);
	ro = mul_mat4(mat4_rotation_x(e->normal.x), mul_mat4(mat4_rotation_y(e->normal.y), mat4_rotation_z(e->normal.z)));
	s = mat4_scale(e->scale.x, e->scale.y, e->scale.z);
	e->tran = mul_mat4(tr, mul_mat4(ro, s));
	e->t_inv = mat4_inverse(e->tran);
	e->t_inv_t = mat4_transpose(e->t_inv);
	new_r.origin = mul_mat4_to_vec(e->t_inv, r.origin, 1);
	new_r.direction = mul_mat4_to_vec(e->t_inv, r.direction, 0);
	float	t = hit_sphere((t_vec){0, 0, 0}, 1.0, new_r);
	// t_vec	hit_local = vec_add(new_r.origin, vec_scale(new_r.direction, t));
	// t_vec	n_local = normalize(hit_local);
	return (t);
}
