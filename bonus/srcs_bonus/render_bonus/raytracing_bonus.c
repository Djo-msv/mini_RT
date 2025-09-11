/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:25:10 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:28:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static t_fcolor	ft_color_ray(t_hit hit, t_scene s, t_ray r, t_fcolor l_int)
{
	t_list		*tmp;
	t_light		*l;
	t_hit		n_h;
	t_fcolor	l_c;
	float		i;

	tmp = s.light;
	while (tmp)
	{
		l = tmp->content;
		r.origin = vec_add(hit.position, vec_mul(hit.normal, 0.0001f));
		r.direction = normalize(vec_sub(l->coordinate, r.origin));
		n_h = intersectscene(s, r, true);
		if (n_h.t <= 0.0 || length(vec_sub(l->coordinate, r.origin)) < n_h.t)
		{
			i = scalar_product(hit.normal, r.direction);
			if (i > 0.0)
			{
				l_c = scale_mlx_color(mlxcolor_to_fcolor(l->color),
						i * l->brightness);
				l_int = add_color(l_int, l_c);
			}
		}
		tmp = tmp->next;
	}
	return (l_int);
}

t_fcolor	shade_raytracing_pixel(t_scene scene, t_ray ray)
{
	t_fcolor	l_intensity;
	t_fcolor	a_light;
	t_hit		hit;

	hit = intersectscene(scene, ray, true);
	if (hit.t <= 0 || hit.type == 3)
	{
		return ((t_fcolor){0.0f, 0.0f, 0.0f});
	}
	l_intensity = (t_fcolor){0.0 ,0.0, 0.0};
	a_light = scalar_color(scale_mlx_color
			(mlxcolor_to_fcolor(scene.a_light.color),
				scene.a_light.ratio), hit.color);
	l_intensity = ft_color_ray(hit, scene, ray, l_intensity);
	l_intensity = scalar_color(l_intensity, hit.color);
	l_intensity = add_color(l_intensity, a_light);
	return (l_intensity);
}
