/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:31:55 by star              #+#    #+#             */
/*   Updated: 2025/07/25 19:42:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	plane(t_hit hit)
{
	hit.color = mlxcolor_to_fcolor(((t_plane *)hit.obj)->color);
	hit.normal = normalize(((t_plane *)hit.obj)->normal);
	return (hit);
}

t_hit	sphere(t_hit hit)
{
	t_sphere	*s;

	s = (t_sphere *)hit.obj;
	hit.color = mlxcolor_to_fcolor(s->color);
	hit.normal = normalize(vec_sub(hit.position, s->coordinate));
	return (hit);
}

t_hit	cylinder(t_hit hit)
{
	if (hit.part == 1)
	{
		t_vec	o_c;
		t_vec	projection;
		float	lenght;

		o_c = vec_sub(hit.position, ((t_cylinder *)hit.obj)->coordinate);
		lenght = scalar_product(o_c, ((t_cylinder *)hit.obj)->normal);
		projection = vec_add(((t_cylinder *)hit.obj)->coordinate, vec_mul(((t_cylinder *)hit.obj)->normal, lenght));
		hit.normal = normalize(vec_sub(hit.position, projection));
	}
	else if (hit.part == 2)
		hit.normal = normalize(((t_cylinder *)hit.obj)->normal);
	else
		hit.normal = vec_mul(((t_cylinder *)hit.obj)->normal, -1);
	return (hit);
}
