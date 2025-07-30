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
	bool		aa;
	t_vec	coordinate;
	t_vec	orientation;
	int		rbon_nb;
	float	rand_h;
	float	rand_v;

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
	t_texture	tex;

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
}	t_cylinder
__attribute__((aligned(1)));

typedef struct s_triangle
{
	t_vec		a;
	t_vec		b;
	t_vec		c;
	mlx_color	color;
	t_vec		normal;
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
}				t_ellipsoid
__attribute__((aligned(1)));

#endif
