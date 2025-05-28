#include "miniRT.h"

static int	init_sphere(t_sphere *sphere, char **args)
{
	char **v;

	if (verfi_float(args[2]))
		return (1);
	sphere->diameter = ft_atof(args[2]);
	v = ft_split(args[3], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255") || verif_int(v[1], "255")
		|| verif_int(v[2], "255"))
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	sphere->color = (t_color){ft_atoi(v[0]), ft_atoi(v[1]), ft_atoi(v[2])};
	ft_free_2d_tab((void **)v);
	return (0);
}

int	parse_sphere(t_scene *scene, char **args)
{
	char		**v;
	t_sphere	*sphere;

	v = ft_split(args[1], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1]) || verfi_float(v[2]))
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	sphere = malloc(sizeof(t_sphere));
	sphere->coordinate = (t_coordinate){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	if (init_sphere(sphere, args))
	{
		free(sphere);
		return (1);
	}
	ft_lstadd_back(&scene->sphere, ft_lstnew(sphere));
	return (0);
}

static int	init_rgb_plane(t_plane *plane, char **args)
{
	char	**v;

	if (verif_fvalue(-1, 1, plane->normal.i)
		|| verif_fvalue(-1, 1, plane->normal.j)
		|| verif_fvalue(-1, 1, plane->normal.k))
		return (1);
	v = ft_split(args[3], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255") || verif_int(v[1], "255")
		|| verif_int(v[2], "255"))
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	plane->color = (t_color){ft_atoi(v[0]), ft_atoi(v[1]), ft_atoi(v[2])};
	ft_free_2d_tab((void **)v);
	return (0);
}

static int	init_normal_plane(t_plane *plane, char **args)
{
	char **v;

	v = ft_split(args[2], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1])
		|| verfi_float(v[2]))
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	plane->normal = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	return (0);
}

int	parse_plane(t_scene *scene, char **args)
{
	char 	**v;
	t_plane	*plane;

	v = ft_split(args[1], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1])
		|| verfi_float(v[2]))
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	plane = malloc(sizeof(t_plane));
	plane->coordinate = (t_coordinate){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	if (init_normal_plane(plane, args) || init_rgb_plane(plane, args))
	{
		free(plane);
		return (1);
	}
	ft_lstadd_back(&scene->plane, ft_lstnew(plane));
	return (0);
}

static int	init_d_h_rgb_cylinder(t_cylinder *cylinder, char **args)
{
	char **v;

	if (verfi_float(args[3]))
		return (1);
	cylinder->diameter = ft_atof(args[3]);
	if (verfi_float(args[4]))
		return (1);
	cylinder->height = ft_atof(args[4]);
	v = ft_split(args[5], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255") || verif_int(v[1], "255")
		|| verif_int(v[2], "255"))
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	cylinder->color = (t_color){ft_atoi(v[0]), ft_atoi(v[1]), ft_atoi(v[2])};
	ft_free_2d_tab((void **)v);
	return (0);
}

static int	init_normal_cylinder(t_cylinder *cylinder, char **args)
{
	char	**v;

	v = ft_split(args[2], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1])
		|| verfi_float(v[2]))
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	cylinder->normal = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	if (verif_fvalue(-1, 1, cylinder->normal.i)
		|| verif_fvalue(-1, 1, cylinder->normal.j)
		|| verif_fvalue(-1, 1, cylinder->normal.k))
		return (1);
	return (0);	
}

int	parse_cylinder(t_scene *scene, char **args)
{
	char 		**v;
	t_cylinder	*cylinder;

	v = ft_split(args[1], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1])
		|| verfi_float(v[2]))
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	cylinder = malloc(sizeof(t_cylinder));
	cylinder->coordinate = (t_coordinate){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	if (init_normal_cylinder(cylinder, args) || init_d_h_rgb_cylinder(cylinder, args) ||
		ft_lstadd_back(&scene->cylinder, ft_lstnew(cylinder)))
	{
		free(cylinder);
		return (1);
	}
	return (0);
}
