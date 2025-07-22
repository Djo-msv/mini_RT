/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:31:55 by star              #+#    #+#             */
/*   Updated: 2025/07/22 19:52:47 by nrolland         ###   ########.fr       */
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

t_hit	sphere(t_data *data, t_hit hit)
{
	if (((t_sphere *)hit.obj)->is_texture)
	{
		mlx_color	pixel;
		t_vec		p;
		int			x;
		int			y;
		float		u;
		float		v;

		p = normalize(vec_sub(hit.position, ((t_sphere *)hit.obj)->coordinate));
		u = 0.5 + atan2(p.z, p.x) / (2 * M_PI);
		v = 0.5 - asin(p.y) / M_PI;
		x = u * data->tex.width;
		y = v * data->tex.height;
		pixel = mlx_get_image_pixel(data->mlx.mlx, data->tex.image, x, y);
		hit.color = mlxcolor_to_fcolor(pixel);
	}
	else
		hit.color = mlxcolor_to_fcolor(((t_sphere *)hit.obj)->color);
	hit.normal = normalize(vec_sub(hit.position, ((t_sphere *)hit.obj)->coordinate));
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

t_hit	ellipsoid(t_hit hit)
{
	t_ellipsoid	*e = (t_ellipsoid *)hit.obj;
	hit.normal = e->n_word;
	hit.position = e->word;
	hit.color = mlxcolor_to_fcolor(e->color);
	return (hit);
}
