/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:25:10 by star              #+#    #+#             */
/*   Updated: 2025/07/26 16:24:07 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_fcolor	ft_color_ray(t_hit hit, t_data *data, t_ray ray, t_fcolor l_int)
{
	t_list		*tmp;
	t_light		*l;
	t_hit		n_h;
	t_fcolor	l_c;
	float		i;

	tmp = data->scene.light;
	while (tmp)
	{
		l = tmp->content;
		ray.origin = vec_add(hit.position, vec_mul(hit.normal, 0.0001f));
		ray.direction = normalize(vec_sub(l->coordinate, ray.origin));
		n_h = intersectscene(data, ray);
		if (n_h.t <= 0.0 || length(vec_sub(l->coordinate, ray.origin)) < n_h.t || n_h.type == 3)
		{
			i = scalar_product(hit.normal, ray.direction);
			if (i > 0.0)
			{
				l_c = scale_mlx_color(mlxcolor_to_fcolor(l->color), i * l->brightness);
				l_int = add_color(l_int, l_c);
			}
		}
		tmp = tmp->next;
	}
	return (l_int);
}

t_fcolor	shade_raytracing_pixel(t_data *data, t_ray ray)
{
	t_fcolor	l_intensity;
	t_fcolor	a_light;
	t_hit		hit;

	l_intensity = (t_fcolor){0.0, 0.0, 0.0};
	a_light = scale_mlx_color(mlxcolor_to_fcolor(data->scene.a_light.color),
			data->scene.a_light.ratio);
	l_intensity = add_color(l_intensity, a_light);
	hit = intersectscene(data, ray);
	if (hit.t <= 0)
		return ((t_fcolor){0.0f, 0.0f, 0.0f});
	l_intensity = ft_color_ray(hit, data, ray, l_intensity);
	hit.color = scalar_color(l_intensity, hit.color);
	return (hit.color);
}
