#ifndef OBJET_H
# define OBJET_H

typedef struct s_a_light
{
	mlx_color	color;

	float		range;
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
	t_vec		coordinate;
	mlx_color	color;

	float		bright;

}	t_light
__attribute__((aligned(1)));

typedef struct s_sphere
{
	t_vec		coordinate;
	mlx_color	color;

	float		diameter;
	float		radius;

}	t_sphere
__attribute__((aligned(1)));

typedef struct s_plane
{
	t_vec		coordinate;
	mlx_color	color;
	t_vec		normal;

}	t_plane
__attribute__((aligned(1)));

typedef struct s_cylinder
{
	t_vec		coordinate;
	mlx_color	color;
	t_vec		normal;
	float		diameter;
	float		radius;
	float		height;
}	t_cylinder
__attribute__((aligned(1)));

typedef struct s_object
{
	t_vec	coordinate;
	mlx_color	color;
	
}	t_object
__attribute__((aligned(1)));


#endif
