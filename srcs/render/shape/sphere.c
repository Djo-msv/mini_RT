/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:02:47 by star              #+#    #+#             */
/*   Updated: 2025/07/26 16:19:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	hit_sphere(t_vec center, double radius, t_ray r)
{
	float	a;
	float	b;
	float	c;
	t_vec	oc;
	float	discriminant;

	if (radius <= 0)
		return (-1);
	oc = vec_sub(center, r.origin);
	a = scalar_product(r.direction, r.direction);
	b = scalar_product(r.direction, oc);
	c = scalar_product(oc, oc) - radius * radius;
	discriminant = b * b - a * c;
	if (discriminant < 0.0)
		return (-1.0);
	else
		return ((b - sqrt(discriminant)) / (a));
}
