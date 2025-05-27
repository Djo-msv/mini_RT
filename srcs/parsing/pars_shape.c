#include "miniRT.h"

// static int	init_sphere(t_scene *scene, char **args)
// {
// 	char **value;

// 	if (verfi_float(args[2]))
// 		return (1);
// 	scene->sphere.diameter = ft_atof(args[2]);
// 	value = ft_split(args[3], ",");
// 	if (!value)
// 		return (1);
// 	if (verif_int(value[0], "255") || verif_int(value[1], "255")
// 		|| verif_int(value[2], "255"))
// 	{
//     	ft_free_2d_tab((void **)value);
// 		return (1);
// 	}
// 	scene->sphere.color.r = ft_atoi(value[0]);
// 	scene->sphere.color.g = ft_atoi(value[1]);
// 	scene->sphere.color.b = ft_atoi(value[2]);
// 	ft_free_2d_tab((void **)value);
// 	return (0);
// }

// int	parse_sphere(t_scene *scene, char **args)
// {
// 	char **value;

// 	value = ft_split(args[1], ",");
// 	if (!value)
// 		return (1);
// 	if (verfi_float(value[0]) || verfi_float(value[1])
// 		|| verfi_float(value[2]))
// 	{
// 	    ft_free_2d_tab((void **)value);
// 		return (1);
// 	}
// 	scene->sphere.coordinate.x = ft_atof(value[0]);
// 	scene->sphere.coordinate.y = ft_atof(value[1]);
// 	scene->sphere.coordinate.z = ft_atof(value[2]);
// 	ft_free_2d_tab((void **)value);
// 	if (init_sphere(scene, args))
// 		return (1);
// 	return (0);
// }

// static int	init_plane(t_scene *scene, char **args)
// {
// 	char	**value;

// 	if (verif_fvalue(-1, 1, scene->plane.normal.i)
// 		|| verif_fvalue(-1, 1, scene->plane.normal.j)
// 		|| verif_fvalue(-1, 1, scene->plane.normal.k))
// 		return (1);
// 	value = ft_split(args[3], ",");
// 	if (!value)
// 		return (1);
// 	if (verif_int(value[0], "255") || verif_int(value[1], "255")
// 		|| verif_int(value[2], "255"))
// 	{
// 		ft_free_2d_tab((void **)value);
// 		return (1);
// 	}
// 	scene->plane.color.r = ft_atoi(value[0]);
// 	scene->plane.color.g = ft_atoi(value[1]);
// 	scene->plane.color.b = ft_atoi(value[2]);
// 	ft_free_2d_tab((void **)value);
// 	return (0);
// }

// int	parse_plane(t_scene *scene, char **args)
// {
// 	char **value;

// 	value = ft_split(args[1], ",");
// 	if (!value)
// 		return (1);
// 	if (verfi_float(value[0]) || verfi_float(value[1])
// 		|| verfi_float(value[2]))
// 	{
// 		ft_free_2d_tab((void **)value);
// 		return (1);
// 	}
// 	scene->plane.coordinate.x = ft_atof(value[0]);
// 	scene->plane.coordinate.y = ft_atof(value[1]);
// 	scene->plane.coordinate.z = ft_atof(value[2]);
// 	ft_free_2d_tab((void **)value);
// 	value = ft_split(args[2], ",");
// 	if (!value)
// 		return (1);
// 	if (verfi_float(value[0]) || verfi_float(value[1])
// 		|| verfi_float(value[2]))
// 	{
// 		ft_free_2d_tab((void **)value);
// 		return (1);
// 	}
// 	scene->plane.normal.i = ft_atof(value[0]);
// 	scene->plane.normal.j = ft_atof(value[1]);
// 	scene->plane.normal.k = ft_atof(value[2]);
// 	ft_free_2d_tab((void **)value);
// 	if (init_plane(scene, args))
// 		return (1);
// 	return (0);
// }

// static int	init_cylinder(t_scene *scene, char **args)
// {
// 	char **value;

// 	if (verfi_float(args[3]))
// 		return (1);
// 	scene->cylinder.diameter = ft_atof(args[3]);
// 	if (verfi_float(args[4]))
// 		return (1);
// 	scene->cylinder.height = ft_atof(args[4]);
// 	value = ft_split(args[5], ",");
// 	if (!value)
// 		return (1);
// 	if (verif_int(value[0], "255") || verif_int(value[1], "255")
// 		|| verif_int(value[2], "255"))
// 	{
// 		ft_free_2d_tab((void **)value);
// 		return (1);
// 	}
// 	scene->cylinder.color.r = ft_atoi(value[0]);
// 	scene->cylinder.color.g = ft_atoi(value[1]);
// 	scene->cylinder.color.b = ft_atoi(value[2]);
// 	ft_free_2d_tab((void **)value);
// 	return (0);
// }

// int	parse_cylinder(t_scene *scene, char **args)
// {
// 	char **value;

// 	value = ft_split(args[1], ",");
// 	if (!value)
// 		return (1);
// 	if (verfi_float(value[0]) || verfi_float(value[1])
// 		|| verfi_float(value[2]))
// 	{
// 		ft_free_2d_tab((void **)value);
// 		return (1);
// 	}
// 	scene->cylinder.coordinate.x = ft_atof(value[0]);
// 	scene->cylinder.coordinate.y = ft_atof(value[1]);
// 	scene->cylinder.coordinate.z = ft_atof(value[2]);
// 	ft_free_2d_tab((void **)value);
// 	value = ft_split(args[2], ",");
// 	if (!value)
// 		return (1);
// 	if (verfi_float(value[0]) || verfi_float(value[1])
// 		|| verfi_float(value[2]))
// 	{
// 		ft_free_2d_tab((void **)value);
// 		return (1);
// 	}
// 	scene->cylinder.normal.i = ft_atof(value[0]);
// 	scene->cylinder.normal.j = ft_atof(value[1]);
// 	scene->cylinder.normal.k = ft_atof(value[2]);
// 	ft_free_2d_tab((void **)value);
// 	if (verif_fvalue(-1, 1, scene->cylinder.normal.i)
// 		|| verif_fvalue(-1, 1, scene->cylinder.normal.j)
// 		|| verif_fvalue(-1, 1, scene->cylinder.normal.k))
// 		return (1);
// 	if (init_cylinder(scene, args))
// 		return (1);
// 	return (0);
// }
