/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathtracing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:35:37 by star              #+#    #+#             */
/*   Updated: 2025/10/02 17:47:35 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec	cosine_weighted_hemisphere(t_vec normal)
{
	t_vec	up;
	t_vec	local;
	float	r1;
	float	r2;

	r1 = drand48();
	r2 = drand48();
	if (fabsf(normal.z) < 0.999f)
		up = (t_vec){0, 0, 1};
	else
		up = (t_vec){1, 0, 0};
	local = vec_add(
			vec_add(vec_mul(normalize(cross(up, normal)),
					sqrtf(r2) * cosf(2.0f * M_PI * r1)),
				vec_mul(cross(normal, normalize(cross(up, normal))),
					sqrtf(r2) * sinf(2.0f * M_PI * r1))),
			vec_mul(normal, sqrtf(1.0f - r2)));
	return (normalize(local));
}

t_fcolor	shade_pathtracing_pixel(t_scene scene, t_ray ray)
{
	int			depth;
	bool		direct_light;
	t_hit		hit;
	t_fcolor	value[3];

	depth = 0;
	direct_light = true;
	value[0] = (t_fcolor){1.0f, 1.0f, 1.0f};
	value[1] = (t_fcolor){0.0f, 0.0f, 0.0f};
	value[2] = scale_mlx_color
		(mlxcolor_to_fcolor(scene.a_light.color),
			scene.a_light.ratio);
	while (depth < 8)
	{
		hit = intersectscene(scene, ray, direct_light);
		if (assign_material(hit, value, &direct_light, &ray))
			break ;
		depth++;
	}
	return (value[1]);
}
