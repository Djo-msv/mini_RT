/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:02:47 by star              #+#    #+#             */
/*   Updated: 2025/07/28 20:04:26 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	hit_sphere(t_vec center, double radius, t_ray r)
{
	t_vec	abc;
	t_vec	oc;
	float	discriminant;
	float	t;

	if (radius <= 0)
		return (-1);
	oc = vec_sub(center, r.origin);
	abc.x = scalar_product(r.direction, r.direction);
	abc.y = scalar_product(r.direction, oc);
	abc.z = scalar_product(oc, oc) - radius * radius;
	discriminant = abc.y * abc.y - abc.x * abc.z;
	if (discriminant < 0.0)
		return (-1.0);
	else
		t = (abc.y - sqrt(discriminant)) / (abc.x);
	if (t < 0.0)
		t = (abc.y + sqrt(discriminant)) / (abc.x);
	return (t);
}
