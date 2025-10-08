/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_texture_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:43:15 by star              #+#    #+#             */
/*   Updated: 2025/10/08 15:03:26 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec	bump_map(t_scene scene, t_hit hit, int x, int y)
{
	mlx_color	pixel;
	t_fcolor	c;
	t_vec		n_m;
	t_vec		normal;
	t_vec		tbn[3];

	tbn[2] = normalize(vec_sub(hit.position,
				((t_sphere *)hit.obj)->coordinate));
	if (!((t_sphere *)hit.obj)->tex.is_normal)
		return (tbn[2]);
	pixel = mlx_get_image_pixel(scene.mlx->mlx,
			((t_sphere *)hit.obj)->tex.n_image, x, y);
	c = mlxcolor_to_fcolor(pixel);
	n_m = (t_vec){c.r * 2.0 - 1.0, c.g * 2.0 - 1.0, c.b * 2.0 - 1.0};
	n_m = normalize(n_m);
	n_m.y = -n_m.y;
	tbn[0] = normalize((t_vec){-sin(atan2(tbn[2].z, tbn[2].x)),
			0, cos(atan2(tbn[2].z, tbn[2].x))});
	tbn[1] = vec_cross(tbn[2], tbn[0]);
	normal = (t_vec){n_m.x * tbn[0].x + n_m.y * tbn[1].x + n_m.z * tbn[2].x,
		n_m.x * tbn[0].y + n_m.y * tbn[1].y + n_m.z * tbn[2].y,
		n_m.x * tbn[0].z + n_m.y * tbn[1].z + n_m.z * tbn[2].z};
	normal = normalize(normal);
	return (normal);
}

void	generate_uv(int *x, int *y, t_hit hit)
{
	t_vec		p;
	float		u;
	float		v;

	p = normalize(vec_sub(hit.position, ((t_sphere *)hit.obj)->coordinate));
	u = 0.5 + atan2(p.z, p.x) / (2 * M_PI);
	v = 0.5 - asin(p.y) / M_PI;
	*x = (1 - u) * ((t_sphere *)hit.obj)->tex.width;
	*y = v * ((t_sphere *)hit.obj)->tex.height;
}

t_fcolor	c_texture(int x, int y, t_hit hit, t_scene scene)
{
	mlx_color	pixel;
	pixel = mlx_get_image_pixel(scene.mlx->mlx,
		((t_sphere *)hit.obj)->tex.image, x, y);
	return (mlxcolor_to_fcolor(pixel));
}
