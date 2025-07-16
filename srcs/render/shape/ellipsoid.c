/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:02:47 by star              #+#    #+#             */
/*   Updated: 2025/07/16 19:35:46 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	hit_ellipsoid(t_ellipsoid *e, t_ray r)
{
	t_ray		new_r;

	new_r.origin = mul_mat4_to_vec(e->t_inv, r.origin, 1);
	new_r.direction = normalize(mul_mat4_to_vec(e->t_inv, r.direction, 0));
	float	t = hit_sphere((t_vec){0, 0, 0}, 1, new_r);
	t_vec	local = vec_add(new_r.origin, vec_scale(new_r.direction, t));
	t_vec	n_local = normalize(local);
	e->word = mul_mat4_to_vec(e->tran, local, 1);
	e->n_word = normalize(mul_mat4_to_vec(e->t_inv_t, n_local, 0));
	if (t < 0.0)
		return (-1);
	return (t);
}
