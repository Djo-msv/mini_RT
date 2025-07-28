/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objet.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:48:43 by star              #+#    #+#             */
/*   Updated: 2025/07/28 15:48:44 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJET_H
# define OBJET_H

typedef struct s_a_light
{
	mlx_color	color;

	float		ratio;
}	t_a_light
__attribute__((aligned(1)));

typedef struct s_cam
{
	t_vec	coordinate;
	t_vec	orientation;

	float	fov;
}	t_cam
__attribute__((aligned(1)));

typedef struct s_light
{
	mlx_color	color;
	t_vec		coordinate;

	float		brightness;

}	t_light
__attribute__((aligned(1)));

typedef struct s_sphere
{
	mlx_color	color;
	t_vec		coordinate;

	float		diameter;
	float		radius;

}	t_sphere
__attribute__((aligned(1)));

typedef struct s_plane
{
	mlx_color	color;
	t_vec		coordinate;

	t_vec		normal;
	float		l_x_pattern;
	float		l_z_pattern;
	mlx_color	pattern_color;
	int			mat;
	int			is_pattern;

}	t_plane
__attribute__((aligned(1)));

typedef struct s_cylinder
{
	mlx_color	color;
	t_vec		coordinate;

	t_vec		normal;
	float		diameter;
	float		radius;
	float		height;
	t_vec		top;
	t_vec		bottom;
}	t_cylinder
__attribute__((aligned(1)));

#endif
