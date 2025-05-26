#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_mlx
{
	mlx_context				mlx;
	mlx_window				win;
	mlx_window_create_info	info;
	mlx_image				img;
}	t_mlx;

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_color;

typedef struct s_a_light
{
	t_color	color;

	float	range;
}	t_a_light;

typedef struct s_cam
{
	t_coordinate	coordinate;
	t_vec			orientation;

	float			fov;
}	t_cam;

typedef struct s_light
{
	t_coordinate	coordinate;
	t_color			color;

	float			bright;

	bool			isset;
}	t_light;

typedef struct s_sphere
{
	t_coordinate	coordinate;
	t_color			color;

	float			diameter;

	bool			isset;
}	t_sphere;

typedef struct s_plane
{
	t_coordinate	coordinate;
	t_vec			normal;
	t_color			color;

	bool		isset;
}	t_plane;

typedef struct s_cylind
{
	t_coordinate	coordinate;
	t_vec			normal;
	t_color			color;

	float			diameter;
	float			height;

	bool			isset;
}	t_cylind;

typedef struct s_scene
{
	t_a_light	a_light;
	t_cam		camera;
	t_light		light;

	t_sphere	sphere;
	t_plane		plane;
	t_cylind	cylinder;
}	t_scene;

typedef struct s_render_image
{
	size_t		nb_images;
	float		coef_new_p;
	float		coef_old_p;
	int			resolution;
	bool		antialiasing;

	mlx_color	*new_img;
	mlx_color	*old_img;
}	t_render_image;

typedef struct s_setting_cam
{
	float	ratio;
	int		width;
	int		height;
	float	focal_length;
	float	viewport_height;
	float	viewport_width;
	int		samples_per_pixel;
	float	pixel_samples_scale;
	int		rbon_nb;

	t_vec	camera_center;
	t_vec	viewport_h;
	t_vec	viewport_v;
	t_vec	pixel_delta_h;
	t_vec	pixel_delta_v;
	t_vec	viewport_upper_left;
	t_vec	pixel00_loc;

	t_vec	**ray_direction;

	float	rand_h;
	float	rand_v;

}	t_setting_cam;

typedef struct s_data
{
	t_mlx			mlx;
	t_scene			scene;
	t_setting_cam	setting_cam;
	t_render_image	image;
}				t_data;

#endif
