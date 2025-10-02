/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:38:05 by star              #+#    #+#             */
/*   Updated: 2025/10/01 19:21:14 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix	mat4_rotation_x(float angle)
{
	float		c;
	float		s;
	t_matrix	r;

	c = cosf(angle);
	s = sinf(angle);
	r = (t_matrix){.m = {{1, 0, 0, 0},
	{0, c, -s, 0},
	{0, s, c, 0},
	{0, 0, 0, 1}}};
	return (r);
}

t_matrix	mat4_rotation_y(float angle)
{
	float		c;
	float		s;
	t_matrix	r;

	c = cosf(angle);
	s = sinf(angle);
	r = (t_matrix){.m = {{c, 0, s, 0},
	{0, 1, 0, 0},
	{-s, 0, c, 0},
	{0, 0, 0, 1}}};
	return (r);
}

t_matrix	mat4_rotation_z(float angle)
{
	float		c;
	float		s;
	t_matrix	r;

	c = cosf(angle);
	s = sinf(angle);
	r = (t_matrix){.m = {{c, -s, 0, 0},
	{s, c, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}}};
	return (r);
}

t_matrix	mat4_translation(float x, float y, float z)
{
	t_matrix	t;

	t = (t_matrix){.m = {{1, 0, 0, x},
	{0, 1, 0, y},
	{0, 0, 1, z},
	{0, 0, 0, 1}}};
	return (t);
}
