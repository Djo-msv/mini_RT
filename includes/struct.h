#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_mlx
{
	mlx_context				mlx;
	mlx_window				win;
	mlx_window_create_info	info;
	mlx_image				img;
}	t_mlx
__attribute__((aligned(1)));

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_color
__attribute__((aligned(1)));

typedef struct s_a_light
{
	t_color	color;

	float	range;
}	t_a_light
__attribute__((aligned(1)));

typedef struct s_cam
{
	t_coordinate	coordinate;
	t_vec			orientation;

	float			fov;
}	t_cam
__attribute__((aligned(1)));

typedef struct s_light
{
	t_coordinate	coordinate;
	t_color			color;

	float			bright;

}	t_light
__attribute__((aligned(1)));

typedef struct s_sphere
{
	t_coordinate	coordinate;
	t_color			color;

	float			diameter;
	float			radius;

}	t_sphere
__attribute__((aligned(1)));

typedef struct s_plane
{
	t_coordinate	coordinate;
	t_vec			normal;
	t_color			color;

}	t_plane
__attribute__((aligned(1)));

typedef struct s_cylinder
{
	t_coordinate		coordinate;
	t_vec				normal;
	t_color				color;

	float				diameter;
	float				radius;
	float				height;

}	t_cylinder
__attribute__((aligned(1)));

typedef struct s_scene
{
	t_a_light	a_light;
	t_cam		camera;
	t_list		*light;
	t_list		*sphere;
	t_list		*plane;
	t_list		*cylinder;
}	t_scene
__attribute__((aligned(1)));

typedef struct s_render_image
{
	size_t		nb_images;
	float		coef_new_p;
	float		coef_old_p;
	int			resolution;
	bool		antialiasing;

	mlx_color	*new_img;
	mlx_color	*old_img;
}	t_render_image
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

typedef struct s_data
{
	t_mlx			mlx;
	t_scene			scene;
	t_setting_cam	setting_cam;
	t_render_image	image;
}				t_data
__attribute__((aligned(1)));

#endif

