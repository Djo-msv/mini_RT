/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:02:47 by star              #+#    #+#             */
/*   Updated: 2025/07/12 17:33:59 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	hit_ellipsoid(t_ellipsoid *e, t_ray r)
{
	t_ray		new_r;

	new_r.origin = mul_mat4_to_vec(e->t_inv, r.origin, 1);
	new_r.direction = mul_mat4_to_vec(e->t_inv, r.direction, 0);
	float	t = hit_sphere((t_vec){0, 0, 0}, 0.5, new_r);
	// printf("%lf alo \n", t);
	return (t);
}
