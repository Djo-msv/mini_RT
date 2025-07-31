/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:38:19 by star              #+#    #+#             */
/*   Updated: 2025/07/31 20:33:32 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	intersectscene(t_scene scene, t_ray ray, bool direct_light)
{
	t_hit	hit;

	hit = nearest_obj(scene, ray, direct_light);
	if (hit.type == 0)
		hit = plane(hit);
	else if (hit.type == 1)
		hit = sphere(scene, hit);
	else if (hit.type == 2)
		hit = cylinder(hit);
	else if (hit.type == 3)
	{
		hit.color = mlxcolor_to_fcolor(((t_light *)hit.obj)->color);
		hit.normal = normalize(vec_sub(hit.position,
				((t_light *)hit.obj)->coordinate));
	}
	else if (hit.type == 4)
	{
		hit.color = mlxcolor_to_fcolor(((t_triangle *)hit.obj)->color);
		hit.normal = ((t_triangle *)hit.obj)->normal;
		hit.material = ((t_triangle *)hit.obj)->mat;
	}
	else if (hit.type == 5)
		hit = ellipsoid(hit);
	return (hit);
}

void	render(t_fcolor *pixel, t_vec ray_direction, t_scene *scene)
{
//	t_setting_cam	camera;
	t_fcolor	tkt;
//	camera = data->setting_cam;
//	return ;

	(void)pixel;
	(void)ray_direction;
	(void)scene;
	(void)tkt;
//	printf("%p \n", pixel);
	if (scene->camera.is_cam)
		*pixel = shade_pathtracing_pixel(*scene, get_antialiasing(*scene, ray_direction));
//	if ((*pixel).r != 0.0f)
//		printf("hello\n");
}
