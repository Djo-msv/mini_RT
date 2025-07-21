/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:38:05 by star              #+#    #+#             */
/*   Updated: 2025/07/21 20:40:45 by star             ###   ########.fr       */
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
	r.m[0][0] = 1;		r.m[0][1] = 0;		r.m[0][2] = 0;		r.m[0][3] = 0;
	r.m[1][0] = 0;		r.m[1][1] = c;		r.m[1][2] = -s;		r.m[1][3] = 0;
	r.m[2][0] = 0;		r.m[2][1] = s;		r.m[2][2] = c;		r.m[2][3] = 0;
	r.m[3][0] = 0;		r.m[3][1] = 0;		r.m[3][2] = 0;		r.m[3][3] = 1;
	return (r);
}


t_matrix	mat4_rotation_y(float angle)
{
	float		c;
	float		s;
	t_matrix	r;

	c = cosf(angle);
	s = sinf(angle);
	r.m[0][0] = c;		r.m[0][1] = 0;		r.m[0][2] = s;		r.m[0][3] = 0;
	r.m[1][0] = 0;		r.m[1][1] = 1;		r.m[1][2] = 0;		r.m[1][3] = 0;
	r.m[2][0] = -s;		r.m[2][1] = 0;		r.m[2][2] = c;		r.m[2][3] = 0;
	r.m[3][0] = 0;		r.m[3][1] = 0;		r.m[3][2] = 0;		r.m[3][3] = 1;
	return (r);
}

t_matrix	mat4_rotation_z(float angle)
{
	float		c;
	float		s;
	t_matrix	r;

	c = cosf(angle);
	s = sinf(angle);
	r.m[0][0] = c;		r.m[0][1] = -s;		r.m[0][2] = 0;		r.m[0][3] = 0;
	r.m[1][0] = s;		r.m[1][1] = c;		r.m[1][2] = 0;		r.m[1][3] = 0;
	r.m[2][0] = 0;		r.m[2][1] = 0;		r.m[2][2] = 1;		r.m[2][3] = 0;
	r.m[3][0] = 0;		r.m[3][1] = 0;		r.m[3][2] = 0;		r.m[3][3] = 1;
	return (r);
}

t_matrix	mat4_translation(float x, float y, float z)
{
	t_matrix	t;

	t.m[0][0] = 1;		t.m[0][1] = 0;		t.m[0][2] = 0;		t.m[0][3] = x;
	t.m[1][0] = 0;		t.m[1][1] = 1;		t.m[1][2] = 0;		t.m[1][3] = y;
	t.m[2][0] = 0;		t.m[2][1] = 0;		t.m[2][2] = 1;		t.m[2][3] = z;
	t.m[3][0] = 0;		t.m[3][1] = 0;		t.m[3][2] = 0;		t.m[3][3] = 1;
	return (t);
}
