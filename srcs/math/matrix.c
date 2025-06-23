/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:08:21 by star              #+#    #+#             */
/*   Updated: 2025/06/23 18:24:24 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	mul_mat4_to_vec(t_matrix m, t_vec v, int is_point)
{
	t_vec	res;

	res.x = m.m[0][0]*v.x + m.m[0][1]*v.y + m.m[0][2]*v.z + m.m[0][3]*is_point;
	res.y = m.m[1][0]*v.x + m.m[1][1]*v.y + m.m[1][2]*v.z + m.m[1][3]*is_point;
	res.z = m.m[2][0]*v.x + m.m[2][1]*v.y + m.m[2][2]*v.z + m.m[2][3]*is_point;
	return (res);
}

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

t_matrix	mul_mat4(t_matrix m1, t_matrix m2)
{
	t_matrix	res;
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			res.m[i][j] = 0;
			while (++k < 4)
				res.m[i][j] += m1.m[i][k]*m2.m[k][j];
		}
	}
	return (res);
}

t_matrix	mat4_scale(float x, float y, float z)
{
	t_matrix	t;

	t.m[0][0] = x;		t.m[0][1] = 0;		t.m[0][2] = 0;		t.m[0][3] = 0;
	t.m[1][0] = 0;		t.m[1][1] = y;		t.m[1][2] = 0;		t.m[1][3] = 0;
	t.m[2][0] = 0;		t.m[2][1] = 0;		t.m[2][2] = z;		t.m[2][3] = 0;
	t.m[3][0] = 0;		t.m[3][1] = 0;		t.m[3][2] = 0;		t.m[3][3] = 1;
	return (t);
}
