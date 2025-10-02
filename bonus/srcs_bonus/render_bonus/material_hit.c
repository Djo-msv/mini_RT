/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:35:32 by jmassavi          #+#    #+#             */
/*   Updated: 2025/10/01 20:37:19 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec	reflect(t_vec v, t_vec n)
{
	return (vec_sub(v, vec_mul(vec_mul(n, scalar_product(v, n)), 2)));
}

void	plastic_light(t_hit	*hit, t_ray *ray, t_fcolor *throughput)
{
	float	cos_theta;

	ray->direction = cosine_weighted_hemisphere(hit->normal);
	ray->origin = vec_add(hit->position, vec_mul(ray->direction, 0.0001f));
	cos_theta = fmaxf(scalar_product(hit->normal, ray->direction), 0.0f);
	*throughput = scalar_color(*throughput, hit->color);
	*throughput = scale_mlx_color(*throughput, cos_theta);
}

void	miror_light(t_hit	*hit, t_ray *ray, t_fcolor *throughput)
{
	ray->direction = reflect(ray->direction, hit->normal);
	ray->origin = vec_add(hit->position, vec_mul(ray->direction, 0.0001f));
	*throughput = scalar_color(*throughput, hit->color);
}

int	assign_material(t_hit hit, t_fcolor value[3],
		bool *direct_light, t_ray *ray)
{
	t_fcolor	emission;

	if (hit.type == -1)
	{
		value[1] = add_color(value[1], scalar_color(
					value[2], value[0]));
		return (1);
	}
	if (hit.type == 3)
	{
		emission = scale_mlx_color(hit.color, ((t_light *)hit.obj)->brightness);
		if (!*direct_light)
			value[1] = add_color(value[1], scalar_color(emission, value[0]));
		else
			return (1);
	}
	if (hit.material == 0)
	{
		plastic_light(&hit, ray, &value[0]);
		*direct_light = false;
	}
	else if (hit.material == 1)
		miror_light(&hit, ray, &value[0]);
	return (0);
}
