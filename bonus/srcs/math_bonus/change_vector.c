/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_vector_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:51:39 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:28:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec	normalize(t_vec v)
{
	t_vec	unit;
	float	length;
	t_vec	zero;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length == 0)
	{
		zero = (t_vec){0, 0, 0};
		return (zero);
	}
	unit.x = v.x / length;
	unit.y = v.y / length;
	unit.z = v.z / length;
	return (unit);
}

t_vec	cross(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec	vec_scale(t_vec v, float s)
{
	t_vec	result;

	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;
	return (result);
}

t_vec	vec_neg(t_vec v)
{
	return ((t_vec){-v.x, -v.y, -v.z});
}
