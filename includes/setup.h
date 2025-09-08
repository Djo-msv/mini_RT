/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:01:01 by star              #+#    #+#             */
/*   Updated: 2025/09/08 18:37:43 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

typedef struct s_fcolor
{
	double	r;
	double	g;
	double	b;
}	t_fcolor
__attribute__((aligned(1)));

# include "image.h"

typedef struct	s_hit
{
	float	t;
	void	*obj;
	int		type;
	int		material;
	int		part;
	t_vec	position;
	t_vec	normal;
	t_fcolor	color;
}	t_hit
__attribute__((aligned(1)));

typedef struct s_camera
{
	bool		move;
	float		fov_rad;
	float		d_height;
	float		d_width;
	float		pitch;
	float		yaw;
	t_vec		forward;
	t_vec		up;
	t_vec		right;
	t_vec		coordinate;
	t_matrix	cam_rotation;
}	t_camera
__attribute__((aligned(1)));

typedef struct	s_param
{
	int	nb_chunk;
}	t_param
__attribute__((aligned(1)));

typedef struct s_mlx
{
	mlx_context		mlx;
	mlx_window		win;
	mlx_window_create_info	info;
	mlx_image		img;
}	t_mlx
__attribute__((aligned(1)));

typedef struct s_scene
{
	t_mlx		*mlx;
	t_a_light	a_light;
	t_cam		camera;
	t_list		*light;
	t_list		*sphere;
	t_list		*plane;
	t_list		*cylinder;
	t_list		*triangle;
	t_list		*ellipsoid;
}	t_scene
__attribute__((aligned(1)));

typedef struct s_select
{
	t_hit		hit;
	int			up_mode;
	int			rotate_mode;
	int			scale_mode;
}				t_select
__attribute__((aligned(1)));

typedef struct s_print_info
{
	t_select	select;
	int		x;
	int		y;
	int		resolution;
	int		nb_input;
	float	fps;
	int	sample;
	bool	aa;
	bool	first_display;
	int		obj;
}	t_print_info
__attribute__((aligned(1)));

typedef struct s_input
{
	bool	z_button;
	bool	s_button;
	bool	a_button;
	bool	d_button;
	bool	space_button;
	bool	shift_button;
	bool	up_button;
	bool	down_button;
	bool	left_button;
	bool	right_button;
	bool	minus_button;
	bool	plus_button;
	bool	deletion_button;
	bool	nine_button;
	bool	zero_button;
	bool	move;
}	t_input
__attribute__((aligned(1)));

typedef struct s_data
{
	struct s_mlx		mlx;
	struct s_scene		scene;
	struct s_tpool		*pool;
	struct s_camera		cam;
	struct s_image		image;
	struct s_param		param;
	struct s_input		input;
	struct s_print_info	info;
}	t_data
__attribute__((aligned(1)));

void	ft_add_texture(t_data *d);

#endif
