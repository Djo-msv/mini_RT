#include "miniRT.h"

int	pars_camera(t_scene *scene, char **args)
{
	char **value;

	if (!args[1])
		return (1);
	value = ft_split(args[1], ",");
	if (!value)
		return (1);
	if (verfi_float(value[0]) || verfi_float(value[1])
		|| verfi_float(value[2]))
	{
		ft_free_2d_tab((void **)value);
		return (1);
	}
	scene->camera.coordinate.x = ft_atof(value[0]);
	scene->camera.coordinate.y = ft_atof(value[1]);
	scene->camera.coordinate.z = ft_atof(value[2]);
	ft_free_2d_tab((void **)value);
	value = ft_split(args[2], ",");
	if (!value)
		return (1);
	if (verfi_float(value[0]) || verfi_float(value[1])
		|| verfi_float(value[2]))
	{
		ft_free_2d_tab((void **)value);
		return (1);
	}
	scene->camera.orientation.i = ft_atof(value[0]);
	scene->camera.orientation.j = ft_atof(value[1]);
	scene->camera.orientation.k = ft_atof(value[2]);
	ft_free_2d_tab((void **)value);
	if (verif_fvalue(-1, 1, scene->camera.orientation.i)
		|| verif_fvalue(-1, 1, scene->camera.orientation.j)
		|| verif_fvalue(-1, 1, scene->camera.orientation.k))
		return (1);
	if (verif_int(args[3], "180"))
		return (1);
	scene->camera.fov = ft_atof(args[3]);
	return (0);
}

int	pars_ambient_light(t_scene *scene, char **args)
{
	char **value;

	if (verfi_float(args[1]))
		return (1);
	scene->a_light.range = ft_atof(args[1]);
	if (verif_fvalue(0.0, 1.0, scene->a_light.range))
		return (1);
	value = ft_split(args[2], ",");
	if (!value)
		return (1);
	if (verif_int(value[0], "255") || verif_int(value[1], "255")
		|| verif_int(value[2], "255"))
	{
	    ft_free_2d_tab((void **)value);
		return (1);
	}
	scene->a_light.color.r = ft_atoi(value[0]);
	scene->a_light.color.g = ft_atoi(value[1]);
	scene->a_light.color.b = ft_atoi(value[2]);
	ft_free_2d_tab((void **)value);
	return (0);
}

int	pars_light(t_scene *scene, char **args)
{
	static int	i = 0;
	char 		**value;

	value = ft_split(args[1], ",");
	if (!value)
		return (1);
	if (verfi_float(value[0]) || verfi_float(value[1])
		|| verfi_float(value[2]))
	{
	    ft_free_2d_tab((void **)value);
		return (1);
	}
	scene->light.coordinate.x = ft_atof(value[0]);
	scene->light.coordinate.y = ft_atof(value[1]);
	scene->light.coordinate.z = ft_atof(value[2]);
	ft_free_2d_tab((void **)value);
	if (verfi_float(args[2]))
		return (1);
	scene->light.bright = ft_atof(args[2]);
	if (verif_fvalue(0, 1, scene->light.bright))
		return (1);
	value = ft_split(args[3], ",");
	if (!value)
		return (1);
	if (verif_int(value[0], "255") || verif_int(value[1], "255")
		|| verif_int(value[2], "255"))
	{
		ft_free_2d_tab((void **)value);
		return (1);
	}
	scene->light.color.r = ft_atoi(value[0]);
	scene->light.color.g = ft_atoi(value[1]);
	scene->light.color.b = ft_atoi(value[2]);
	ft_free_2d_tab((void **)value);
	i++;
	return (0);
}
