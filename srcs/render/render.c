/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:21:13 by star              #+#    #+#             */
/*   Updated: 2025/07/22 15:25:14 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	intersectScene(t_data *data, t_ray ray)
{
	t_hit	hit;

	hit = nearest_obj(data, ray);
	if (hit.type == 0)
		hit = plane(hit);
	else if (hit.type == 1)
		hit = sphere(data, hit);
	else if (hit.type == 2)
		hit = cylinder(hit);
	else if (hit.type == 3)
	{
		hit.color = mlxcolor_to_fcolor(((t_light *)hit.obj)->color);
		hit.normal = normalize(vec_sub(hit.position, ((t_light *)hit.obj)->coordinate));	
	}
	else if (hit.type == 4)
	{
		hit.color = mlxcolor_to_fcolor(((t_triangle *)hit.obj)->color);
		hit.normal = ((t_triangle *)hit.obj)->normal;
	}
	else if (hit.type == 5)
		hit = ellipsoid(hit);
	return (hit);
}

void	render(t_data *data, t_fcolor *pixel, t_vec ray_direction)
{
//	t_setting_cam	camera;

//	camera = data->setting_cam;
	sampling(pixel, shade_pathtracing_pixel(data, get_antialiasing(data, ray_direction)),
		  data->image.coef_new_p, data->image.coef_old_p);
}
