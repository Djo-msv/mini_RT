/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:21:13 by star              #+#    #+#             */
/*   Updated: 2025/09/17 17:48:26 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	intersectscene(t_data *data, t_ray ray, bool direct_light)
{
	t_hit	hit;

	hit = nearest_obj(data, ray, direct_light);
	if (hit.type == 0)
		hit = plane(hit);
	else if (hit.type == 1)
		hit = sphere(hit);
	else if (hit.type == 2)
		hit = cylinder(hit);
	else if (hit.type == 3)
	{
		hit.color = mlxcolor_to_fcolor(((t_light *)hit.obj)->color);
		hit.normal = normalize(vec_sub(hit.position,
					((t_light *)hit.obj)->coordinate));
	}
	if (hit.obj)
	{
		if (scalar_product(hit.normal, ray.direction) > 0)
			hit.normal = vec_scale(hit.normal, -1);
	}
	return (hit);
}

void	render(t_data *data, t_fcolor *pixel, t_vec ray_direction)
{
	if (data->scene.camera.is_cam)
	{
		sampling(pixel, shade_raytracing_pixel(data,
				get_antialiasing(data, ray_direction)),
			data->image.coef_new_p, data->image.coef_old_p);
	}
}
