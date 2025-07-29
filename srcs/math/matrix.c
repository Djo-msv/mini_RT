/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:08:21 by star              #+#    #+#             */
/*   Updated: 2025/07/29 17:00:05 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	mul_mat4_to_vec(t_matrix m, t_vec v, int is_point)
{
	t_vec	res;

	res.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2]
		* v.z + m.m[0][3] * is_point;
	res.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2]
		* v.z + m.m[1][3] * is_point;
	res.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2]
		* v.z + m.m[2][3] * is_point;
	return (res);
}

t_matrix	mul_mat4(t_matrix m1, t_matrix m2)
{
	t_matrix	res;
	int			i;
	int			j;
	int			k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			res.m[i][j] = 0;
			while (++k < 4)
				res.m[i][j] += m1.m[i][k] * m2.m[k][j];
		}
	}
	return (res);
}

t_matrix	mat4_scale(float x, float y, float z)
{
	t_matrix	t;

	t = (t_matrix){.m = {{x, 0, 0, 0},
	{0, y, 0, 0},
	{0, 0, z, 0},
	{0, 0, 0, 1}}};
	return (t);
}

t_matrix	mat4_transpose(t_matrix m)
{
	t_matrix	t;
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			t.m[i][j] = m.m[j][i];
	}
	return (t);
}
