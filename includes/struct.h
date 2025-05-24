#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_a_light
{
	float		range;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
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
	float	bright;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	bool	isset;
}				t_light;

typedef struct s_sphere
{
	float	x;
	float	y;
	float	z;
	float	d;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
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
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
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
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	bool	isset;
}				t_cylind;

typedef struct s_scene
{
	t_a_light	a_light;
	t_cam		camera;
	t_light		light[256];

	t_sphere	sphere[4096];
	t_plane		plane[4096];
	t_cylind	cylinder[4096];
}	t_scene;

typedef struct s_mlx
{
    mlx_context mlx;
    mlx_window win;
	mlx_window_create_info info;
	mlx_image	img;
} t_mlx;

typedef struct s_data
{
	t_mlx	mlx;
	t_scene	scene;
}				t_data;

int	parse(t_data *d, int argc, char **argv);

#endif
