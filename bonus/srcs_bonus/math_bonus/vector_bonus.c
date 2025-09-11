/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:47:02 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:28:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec	vec_add(t_vec vec1, t_vec vec2)
{
	return ((t_vec){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_vec	vec_sub(t_vec vec1, t_vec vec2)
{
	return ((t_vec){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
}

t_vec	vec_mul(t_vec vec, float mult)
{
	return ((t_vec){vec.x * mult, vec.y * mult, vec.z * mult});
}

t_vec	vec_div(t_vec vec, float div)
{
	if (div == 0.0f)
		return ((t_vec){0.0f, 0.0f, 0.0f});
	return ((t_vec){vec.x / div, vec.y / div, vec.z / div});
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	return ((t_vec){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x});
}
