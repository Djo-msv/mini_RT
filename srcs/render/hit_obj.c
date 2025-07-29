/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:31:55 by star              #+#    #+#             */
/*   Updated: 2025/07/29 17:37:58 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	plane(t_hit hit)
{
	int	checker;

	if (((t_plane *)hit.obj)->is_pattern)
	{
		checker = ((int)floor(hit.position.x / ((t_plane *)hit.obj)->l_x_pattern)
				+ (int)floor(hit.position.z / ((t_plane *)hit.obj)->l_x_pattern)) % 2;
		if (checker)
			hit.color = mlxcolor_to_fcolor(((t_plane *)hit.obj)->color);
		else 
			hit.color = mlxcolor_to_fcolor(((t_plane *)hit.obj)->pattern_color);
	}
	else
		hit.color = mlxcolor_to_fcolor(((t_plane *)hit.obj)->color);
	hit.normal = normalize(((t_plane *)hit.obj)->normal);
	hit.material = ((t_plane *)hit.obj)->mat;
	return (hit);
}

t_hit	sphere(t_scene scene, t_hit hit)
{
	t_sphere	*s;

	s = (t_sphere *)hit.obj;
	if (s->tex.is_texture)
	{
		mlx_color	pixel;
		t_vec		p;
		int			x;
		int			y;
		float		u;
		float		v;

		p = normalize(vec_sub(hit.position, s->coordinate));
		u = 0.5 + atan2(p.z, p.x) / (2 * M_PI);
		v = 0.5 - asin(p.y) / M_PI;
		x = u * s->tex.width;
		y = v * s->tex.height;
		pixel = mlx_get_image_pixel(scene.mlx->mlx, s->tex.image, x, y);
		hit.color = mlxcolor_to_fcolor(pixel);
	}
	else
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
	hit.color = mlxcolor_to_fcolor(((t_cylinder *)hit.obj)->color);
	return (hit);
}

t_hit	ellipsoid(t_hit hit)
{
	t_ellipsoid	*e = (t_ellipsoid *)hit.obj;
	hit.color = mlxcolor_to_fcolor(e->color);
	return (hit);
}
