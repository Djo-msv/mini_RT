/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:00:30 by star              #+#    #+#             */
/*   Updated: 2025/07/30 17:00:31 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef struct s_matrix
{
	float	m[4][4];
}				t_matrix;

t_vec		mul_mat4_to_vec(t_matrix m, t_vec v, int is_point);
t_matrix	mat4_rotation_y(float angle);
t_matrix	mat4_rotation_z(float angle);
t_matrix	mat4_rotation_x(float angle);
t_matrix	mat4_translation(float x, float y, float z);
t_matrix	mul_mat4(t_matrix m1, t_matrix m2);
t_matrix	mat4_scale(float x, float y, float z);
t_matrix	mat4_transpose(t_matrix m);
t_matrix	mat4_inverse(t_matrix m);

#endif