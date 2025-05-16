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
	int			x;
	int			y;
	int			z;
	int			orient_x;
	int			orient_y;
	int			orient_z;
	int			fov;
}				t_cam;

typedef struct s_light
{
	int			x;
	int			y;
	int			z;
	int			bright;
	//add (unused in mandatory part) R, G, B colors in the range..
}				t_light;

typedef struct s_sphere
{
	int			x;
	int			y;
	int			z;
	int			d;
	int			r;
	int			g;
	int			b;
}				t_sphere;

typedef struct s_plane
{
	int			x;
	int			y;
	int			z;
	int			normal_x;
	int			normal_y;
	int			normal_z;
	int			r;
	int			g;
	int			b;
}				t_plane;

typedef struct s_cylind
{
	int			x;
	int			y;
	int			z;
	int			normal_x;
	int			normal_y;
	int			normal_z;
	int			d;
	int			height;
}				t_cylind;

typedef struct s_data
{
	int		 mouffette;
}				t_data;

int	parse(t_data *d, int argc, char **argv);

#endif
