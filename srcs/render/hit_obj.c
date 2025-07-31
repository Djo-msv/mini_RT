/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:31:55 by star              #+#    #+#             */
/*   Updated: 2025/07/31 18:10:35 by star             ###   ########.fr       */
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

t_vec	bump_map(t_scene scene, t_hit hit, int x, int y)
{
	mlx_color	pixel;
	t_vec		TBN[3]; //Tangent, Bitangent, Normal
	t_vec		n_map;
	t_fcolor	c;
	t_vec		normal;

	TBN[2] = normalize(vec_sub(hit.position, ((t_sphere *)hit.obj)->coordinate));
	if (!((t_sphere *)hit.obj)->tex.is_normal)
		return (TBN[2]);
	pixel = mlx_get_image_pixel(scene.mlx->mlx, ((t_sphere *)hit.obj)->tex.n_image, x, y);
	c = mlxcolor_to_fcolor(pixel);
	n_map = (t_vec){c.r * 2.0 - 1.0, c.g * 2.0 - 1.0, c.b * 2.0 - 1.0};
	n_map = normalize(n_map);
	TBN[0] = normalize((t_vec){-sin(atan2(TBN[2].z, TBN[2].x)), 0, cos(atan2(TBN[2].z, TBN[2].x))});
	TBN[1] = vec_cross(TBN[2], TBN[0]);
	normal = (t_vec){n_map.x * TBN[0].x + n_map.y * TBN[1].x + n_map.z * TBN[2].x,
					n_map.x * TBN[0].y + n_map.y * TBN[1].y + n_map.z * TBN[2].y,
					n_map.x * TBN[0].z + n_map.y * TBN[1].z + n_map.z * TBN[2].z};
	normal = normalize(normal);
	return (normal);
}

t_fcolor	c_texture(int *x, int *y, t_hit hit, t_scene scene)
{
	mlx_color	pixel;
	t_vec		p;
	float		u;
	float		v;

	p = normalize(vec_sub(hit.position, ((t_sphere *)hit.obj)->coordinate));
	u = 0.5 + atan2(p.z, p.x) / (2 * M_PI);
	v = 0.5 - asin(p.y) / M_PI;
	*x = u * ((t_sphere *)hit.obj)->tex.width;
	*y = v * ((t_sphere *)hit.obj)->tex.height;
	pixel = mlx_get_image_pixel(scene.mlx->mlx, ((t_sphere *)hit.obj)->tex.image, *x, *y);
	return (mlxcolor_to_fcolor(pixel));
}

t_hit	sphere(t_scene scene, t_hit hit)
{
	t_sphere	*s;
	int			x;
	int			y;

	x = 0;
	y = 0;
	s = ((t_sphere *)hit.obj);
	if (s->tex.is_texture)
		hit.color = c_texture(&x, &y, hit, scene);
	else
		hit.color = mlxcolor_to_fcolor(s->color);
	hit.normal = bump_map(scene, hit, x, y);
	hit.material = s->mat;
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
	hit.material = ((t_cylinder *)hit.obj)->mat;
	return (hit);
}

t_hit	ellipsoid(t_hit hit)
{
	t_ellipsoid	*e = (t_ellipsoid *)hit.obj;
	hit.color = mlxcolor_to_fcolor(e->color);
	hit.material = e->mat;
	return (hit);
}
