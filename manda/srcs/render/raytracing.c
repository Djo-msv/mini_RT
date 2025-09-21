/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:25:10 by star              #+#    #+#             */
/*   Updated: 2025/09/17 17:57:59 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_fcolor	ft_l_intensity(t_hit hit, t_ray ray, t_fcolor l_int, t_light *l)
{
	float		i;
	t_fcolor	l_c;

	i = scalar_product(hit.normal, ray.direction);
	if (i > 0.0)
	{
		l_c = scale_mlx_color(mlxcolor_to_fcolor(l->color), i * l->brightness);
		l_int = add_color(l_int, l_c);
	}
	return (l_int);
}

t_fcolor	ft_color_ray(t_hit hit, t_data *data, t_ray ray, t_fcolor l_int)
{
	t_list		*tmp;
	t_light		*l;
	t_hit		n_h;

	tmp = data->scene.light;
	while (tmp)
	{
		l = tmp->content;
		ray.origin = vec_add(hit.position, vec_mul(hit.normal, 0.0001f));
		ray.direction = normalize(vec_sub(l->coordinate, ray.origin));
		n_h = intersectscene(data, ray, false);
		if (n_h.t <= 0.0 || length(vec_sub(l->coordinate, ray.origin)) < n_h.t)
			l_int = ft_l_intensity(hit, ray, l_int, l);
		tmp = tmp->next;
	}
	return (l_int);
}

t_fcolor	shade_raytracing_pixel(t_data *d, t_ray ray)
{
	t_fcolor	l_intensity;
	t_fcolor	a_light;
	t_hit		hit;

	hit = intersectscene(d, ray, false);
	if (hit.t <= 0 || hit.type == 3)
		return ((t_fcolor){0.0f, 0.0f, 0.0f});
	l_intensity = (t_fcolor){0.0, 0.0, 0.0};
	a_light = scalar_color(scale_mlx_color
			(mlxcolor_to_fcolor(d->scene.a_light.color),
				d->scene.a_light.ratio), hit.color);
	l_intensity = ft_color_ray(hit, d, ray, l_intensity);
	l_intensity = scalar_color(l_intensity, hit.color);
	l_intensity = add_color(l_intensity, a_light);
	return (l_intensity);
}
