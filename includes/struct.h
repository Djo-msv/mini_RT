#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_a_light
{
	float		range;
	int			r;
	int			g;
	int			b;
}				t_a_light;

typedef struct s_cam
{
	float	x;
	float	y;
	float	z;
	float	orient_x;
	float	orient_y;
	float	orient_z;
	float	fov;
}				t_cam;

typedef struct s_light
{
	float	x;
	float	y;
	float	z;
	int		r;
	int		g;
	int		b;
	float	bright;
	bool	isset;
	//add (unused in mandatory part) R, G, B colors in the range..
}				t_light;

typedef struct s_sphere
{
	float	x;
	float	y;
	float	z;
	float	d;
	int		r;
	int		g;
	int		b;
	bool	isset;
}				t_sphere;

typedef struct s_plane
{
	float	x;
	float	y;
	float	z;
	float	normal_x;
	float	normal_y;
	float	normal_z;
	int		r;
	int		g;
	int		b;
	bool	isset;
}				t_plane;

typedef struct s_cylind
{
	float	x;
	float	y;
	float	z;
	float	normal_x;
	float	normal_y;
	float	normal_z;
	float	d;
	float	height;
	int		r;
	int		g;
	int		b;
	bool	isset;
}				t_cylind;

typedef struct s_mlx
{
    mlx_context mlx;
    mlx_window win;
	mlx_window_create_info info;
	mlx_image	img;
} t_mlx;

typedef struct s_scene
{
	t_a_light	a_light;
	t_cam		camera;
	t_light		light[256];

	t_sphere	sphere[4096];
	t_plane		plane[4096];
	t_cylind	cylinder[4096];
}	t_scene;

typedef struct s_image
{
	size_t		nb_images;
	float		coef_new_p;
	float		coef_old_p;
	mlx_color	*new_img;
	mlx_color	*old_img;
}	t_image;

typedef struct t_param
{
	int		resolution;
	int		rbon_nb;
	bool	antialiasing;
}	t_param;

typedef struct s_data
{
	t_mlx	mlx;
	t_scene	scene;
	t_param	param;
	t_image	image;
}				t_data;

int	parse(t_data *d, int argc, char **argv);

#endif
