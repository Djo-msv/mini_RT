/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objet.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:00:44 by star              #+#    #+#             */
/*   Updated: 2025/07/30 18:48:34 by star             ###   ########.fr       */
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
	int		rbon_nb;
	float	rand_h;
	float	rand_v;
	int		fov;
	int		is_cam;
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
	t_texture	tex;
	int			mat;

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
	int			mat;
}	t_cylinder
__attribute__((aligned(1)));

typedef struct s_triangle
{
	t_vec		a;
	t_vec		b;
	t_vec		c;
	mlx_color	color;
	t_vec		normal;
	int			mat;
}				t_triangle
__attribute__((aligned(1)));

typedef struct s_ellipsoid
{
	mlx_color	color;
	t_vec		coordinate;
	t_vec		rotation;
	t_vec		scale;
	float		size;
	t_matrix	tran;
	t_matrix	t_inv;
	t_matrix	t_inv_t;
	int			mat;
}				t_ellipsoid
__attribute__((aligned(1)));

#endif
