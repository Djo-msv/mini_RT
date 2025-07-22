/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest_elli_cyl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:22:04 by star              #+#    #+#             */
/*   Updated: 2025/07/22 15:56:59 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	nearest_ellipsoid(t_data *data, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_ellipsoid	*ellipsoid;
	float		t;

	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = data->scene.ellipsoid;
	while (tmp)
	{
		ellipsoid = (t_ellipsoid *)tmp->content;
		t = hit_ellipsoid(ellipsoid, ray);
		if (t > 0.0f && (t < hit.t || hit.t == 0))
		{
			hit.t = t;
			hit.obj = ellipsoid;
			hit.type = 5;
		}
		tmp = tmp->next;
	}
	return (hit);
}

t_hit	cylinder_part(t_cylinder *cy, t_ray ray)
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
	t[1] = hit_base_cylinder(cy, cy->top, ray);
	t[2] = hit_base_cylinder(cy, cy->bottom, ray);
	while (++i < 2)
	{
		if (t[i] > 0.0f && (t[i] < hit.t || hit.t == 0))
		{
			hit.t = t[i];
			hit.part = i + 1;
		}
	}
	return (hit);
}

t_hit	nearest_cylinder(t_data *data, t_ray ray)
{
	t_hit		hit;
	t_hit		n;
	t_list		*tmp;
	t_cylinder	*cylinder;
	
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	hit.part = 0;
	tmp = data->scene.cylinder;
	while (tmp)
	{
		cylinder = (t_cylinder *)tmp->content;
		n = cylinder_part(cylinder, ray);
		if (n.t > 0.0f && (n.t < hit.t || hit.t == 0))
			hit = n;
		tmp = tmp->next;
	}
	return (hit);
}
