/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:22:10 by star              #+#    #+#             */
/*   Updated: 2025/07/28 19:52:57 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	nearest_plane(t_data *data, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_plane		*plane;
	float		t;

	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = data->scene.plane;
	while (tmp)
	{
		plane = (t_plane *)tmp->content;
		t = hit_plane(plane->coordinate, plane->normal, ray);
		if (t > 0.0f && (t < hit.t || hit.t == 0))
		{
			hit.t = t;
			hit.obj = plane;
			hit.type = 0;
		}
		tmp = tmp->next;
	}
	return (hit);
}

t_hit	nearest_light(t_data *data, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_light		*light;
	float		t;

	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = data->scene.light;
	while (tmp)
	{
		light = (t_light *)tmp->content;
		t = hit_sphere(light->coordinate, 3.0f, ray);
		if (t > 0.0f && (t < hit.t || hit.t == 0))
		{
			hit.t = t;
			hit.obj = light;
			hit.type = 3;
		}
		tmp = tmp->next;
	}
	return (hit);
}

t_hit	nearest_sphere(t_data *data, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_sphere	*sphere;
	float		t;

	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = data->scene.sphere;
	while (tmp)
	{
		sphere = (t_sphere *)tmp->content;
		t = hit_sphere(sphere->coordinate, sphere->radius, ray);
		if (t > 0.0f && (t < hit.t || hit.t == 0))
		{
			hit.t = t;
			hit.obj = sphere;
			hit.type = 1;
		}
		tmp = tmp->next;
	}
	return (hit);
}

t_hit	nearest_obj(t_data *data, t_ray ray, bool direct_light)
{
	t_hit	hit;
	t_hit	buf_hit;

	hit = nearest_sphere(data, ray);
	buf_hit = nearest_plane(data, ray);
	if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
		hit = buf_hit;
	buf_hit = nearest_cylinder(data, ray);
	if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
		hit = buf_hit;
	if (direct_light)
	{
		buf_hit = nearest_light(data, ray);
		if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
			hit = buf_hit;
	}
	hit.position = vec_add(ray.origin, vec_mul(ray.direction, hit.t));
	return (hit);
}
