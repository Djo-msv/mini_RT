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

typedef struct s_setting_cam
{
	float	ratio;
	int		width;
	int		height;
	float	focal_length;
	float	viewport_height;
	float	viewport_width;
	float	pixel_samples_scale;
	int		rbon_nb;
	float	yaw;
	float	pitch;

	t_vec	camera_center;
	t_vec	viewport_h;
	t_vec	viewport_v;
	t_vec	pixel_delta_h;
	t_vec	pixel_delta_v;
	t_vec	viewport_upper_left;
	t_vec	pixel00_loc;
	t_vec	forward;

	t_vec	**ray_direction;

	float	rand_h;
	float	rand_v;
	float	res_h;
	float	res_v;

	bool	move;

}	t_setting_cam
__attribute__((aligned(1)));

typedef struct s_select
{
	t_hit		hit;
	int			up_mode;
	int			rotate_mode;
}				t_select
__attribute__((aligned(1)));

typedef struct s_scene
{
	t_a_light	a_light;
	t_cam		camera;
	t_list		*light;
	t_list		*sphere;
	t_list		*plane;
	t_list		*cylinder;
	t_list		*triangle;
	t_list		*ellipsoid;
	t_select	select;
}	t_scene
__attribute__((aligned(1)));

typedef struct s_mlx
{
	mlx_context				mlx;
	mlx_window				win;
	mlx_window_create_info	info;
	mlx_image				img;
}	t_mlx
__attribute__((aligned(1)));

typedef struct s_data
{
	struct s_mlx			mlx;
	struct s_scene			scene;
	struct s_setting_cam	setting_cam;
	struct s_image			image;
}	t_data
__attribute__((aligned(1)));

#endif
