/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:25:10 by star              #+#    #+#             */
/*   Updated: 2025/07/24 16:34:57 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_fcolor	ft_color_ray(t_hit hit, t_data *data, t_ray ray, t_fcolor l_intensity)
{
	t_list		*tmp;
	t_light		*l;
	t_hit		new_hit;
	t_fcolor	l_color;
	float		intensity;

	tmp = data->scene.light;
	while (tmp)
	{
		l = tmp->content;
		ray.origin = vec_add(hit.position, vec_mul(hit.normal, 0.0001f));
		ray.direction = normalize(vec_sub(l->coordinate, ray.origin));
		new_hit = intersectScene(data, ray);
		if (new_hit.t <= 0.0 || length(vec_sub(l->coordinate, ray.origin)) < new_hit.t || new_hit.type == 3)
		{
			intensity = scalar_product(hit.normal, ray.direction);
			if (intensity > 0.0)
			{
				l_color = scale_mlx_color(mlxcolor_to_fcolor(l->color), intensity * l->brightness);
				l_intensity = add_color(l_intensity, l_color);
			}
		}
		tmp = tmp->next;
	}
	return (l_intensity);
}


t_fcolor	shade_raytracing_pixel(t_data *data, t_ray ray)
{
	t_fcolor	l_intensity;
	t_fcolor	a_light;
	t_hit		hit;

	l_intensity = (t_fcolor){0.0, 0.0, 0.0};
	a_light = scale_mlx_color(mlxcolor_to_fcolor(data->scene.a_light.color), data->scene.a_light.ratio);
	l_intensity = add_color(l_intensity, a_light);
	hit = intersectScene(data, ray);
	if (hit.t <= 0)
		return ((t_fcolor){0.0f, 0.0f, 0.0f});
	l_intensity = ft_color_ray(hit, data, ray, l_intensity);
	hit.color = scalar_color(l_intensity, hit.color);
	return (hit.color);
}
