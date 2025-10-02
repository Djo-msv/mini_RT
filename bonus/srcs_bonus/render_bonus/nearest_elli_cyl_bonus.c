/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest_elli_cyl_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:22:04 by star              #+#    #+#             */
/*   Updated: 2025/10/01 20:43:59 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_hit	nearest_triangle(t_scene scene, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_triangle	*triangle;
	float		t;

	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	hit.material = 0;
	tmp = scene.triangle;
	while (tmp)
	{
		triangle = (t_triangle *)tmp->content;
		t = hit_triangle(triangle, ray);
		if (t > 0.0f && t < RENDER_DISTANCE && (t < hit.t || hit.t == 0))
		{
			hit.t = t;
			hit.obj = triangle;
			hit.type = 4;
		}
		tmp = tmp->next;
	}
	return (hit);
}

t_hit	nearest_ellipsoid(t_scene scene, t_ray ray)
{
	t_hit		hit;
	t_hit		hit_tmp;
	t_list		*tmp;
	t_ellipsoid	*ellipsoid;
	float		t;

	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = scene.ellipsoid;
	while (tmp)
	{
		ellipsoid = (t_ellipsoid *)tmp->content;
		t = hit_ellipsoid(ellipsoid, ray, &hit_tmp);
		if (t > 0.0f && t < RENDER_DISTANCE && (t < hit.t || hit.t == 0))
		{
			hit = hit_tmp;
			hit.type = 5;
		}
		tmp = tmp->next;
	}
	return (hit);
}

static t_hit	cylinder_part(t_cylinder *cy, t_ray ray)
{
	float	t[3];
	t_hit	hit;
	int		i;

	i = -1;
	hit.t = 0;
	hit.obj = cy;
	hit.type = 2;
	hit.part = 0;
	t[0] = hit_cylinder(cy, cy->radius, ray);
	t[1] = hit_base_cylinder(cy, vec_add(cy->coordinate,
				vec_mul(cy->normal, cy->height / 2)), ray);
	t[2] = hit_base_cylinder(cy, vec_sub(cy->coordinate,
				vec_mul(cy->normal, cy->height / 2)), ray);
	while (++i < 3)
	{
		if (t[i] > 0.0f && (t[i] < hit.t || hit.t == 0))
		{
			hit.t = t[i];
			hit.part = i + 1;
		}
	}
	return (hit);
}

t_hit	nearest_cylinder(t_scene scene, t_ray ray)
{
	t_hit		hit;
	t_hit		n;
	t_list		*tmp;
	t_cylinder	*cylinder;

	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	hit.part = 0;
	tmp = scene.cylinder;
	while (tmp)
	{
		cylinder = (t_cylinder *)tmp->content;
		n = cylinder_part(cylinder, ray);
		if (n.t > 0.0f && n.t < RENDER_DISTANCE && (n.t < hit.t || hit.t == 0))
			hit = n;
		tmp = tmp->next;
	}
	return (hit);
}

void	nearest_obj_bonus(t_scene scene, t_ray ray, t_hit *hit)
{
	t_hit	buf_hit;

	buf_hit = nearest_triangle(scene, ray);
	if (buf_hit.t > 0.0f && (buf_hit.t < hit->t || hit->t == 0))
		*hit = buf_hit;
	buf_hit = nearest_ellipsoid(scene, ray);
	if (buf_hit.t > 0.0f && (buf_hit.t < hit->t || hit->t == 0))
		*hit = buf_hit;
	else
		hit->position = vec_add(ray.origin, vec_mul(ray.direction, hit->t));
}
