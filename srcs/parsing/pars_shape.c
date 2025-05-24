#include "miniRT.h"

int	pars_sphere(t_scene *scene, char **args)
{
	static int	i = 0;
	char **value;

	value = ft_split(args[1], ",");
	if (!value)
		return (1);
	if (verfi_float(value[0]) || verfi_float(value[1])
		|| verfi_float(value[2]))
	{
		ft_free_2d_tab(value);
		return (1);
	}
	scene->sphere[i].x = ft_atof(value[0]);
	scene->sphere[i].y = ft_atof(value[1]);
	scene->sphere[i].z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	if (verfi_float(args[2]))
		return (1);
	scene->sphere[i].d = ft_atof(args[2]);
	value = ft_split(args[3], ",");
	if (!value)
		return (1);
	if (verif_int(value[0], "255") || verif_int(value[1], "255")
		|| verif_int(value[2], "255"))
	{
		ft_free_2d_tab(value);
		return (1);
	}
	scene->sphere[i].r = ft_atoi(value[0]);
	scene->sphere[i].g = ft_atoi(value[1]);
	scene->sphere[i].b = ft_atoi(value[2]);
	scene->sphere[i].isset = true;
	ft_free_2d_tab(value);
	i++;
	return (0);
}

int	pars_plane(t_scene *scene, char **args)
{
	static int	i = 0;
	char **value;

	value = ft_split(args[1], ",");
	if (!value)
		return (1);
	if (verfi_float(value[0]) || verfi_float(value[1])
		|| verfi_float(value[2]))
	{
		ft_free_2d_tab(value);
		return (1);
	}
	scene->plane[i].x = ft_atof(value[0]);
	scene->plane[i].y = ft_atof(value[1]);
	scene->plane[i].z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	value = ft_split(args[2], ",");
	if (!value)
		return (1);
	if (verfi_float(value[0]) || verfi_float(value[1])
		|| verfi_float(value[2]))
	{
		ft_free_2d_tab(value);
		return (1);
	}
	scene->plane[i].normal_x = ft_atof(value[0]);
	scene->plane[i].normal_y = ft_atof(value[1]);
	scene->plane[i].normal_z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	if (verif_fvalue(-1, 1, scene->plane[i].normal_x)
		|| verif_fvalue(-1, 1, scene->plane[i].normal_y)
		|| verif_fvalue(-1, 1, scene->plane[i].normal_z))
		return (1);
	value = ft_split(args[3], ",");
	if (!value)
		return (1);
	if (verif_int(value[0], "255") || verif_int(value[1], "255")
		|| verif_int(value[2], "255"))
	{
		ft_free_2d_tab(value);
		return (1);
	}
	scene->plane[i].r = ft_atoi(value[0]);
	scene->plane[i].g = ft_atoi(value[1]);
	scene->plane[i].b = ft_atoi(value[2]);
	scene->plane[i].isset = true;
	ft_free_2d_tab(value);
	i++;
	return (0);
}

int	pars_cylinder(t_scene *scene, char **args)
{
	static int	i = 0;
	char **value;

	value = ft_split(args[1], ",");
	if (!value)
		return (1);
	if (verfi_float(value[0]) || verfi_float(value[1])
		|| verfi_float(value[2]))
	{
		ft_free_2d_tab(value);
		return (1);
	}
	scene->cylinder[i].x = ft_atof(value[0]);
	scene->cylinder[i].y = ft_atof(value[1]);
	scene->cylinder[i].z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	value = ft_split(args[2], ",");
	if (!value)
		return (1);
	if (verfi_float(value[0]) || verfi_float(value[1])
		|| verfi_float(value[2]))
	{
		ft_free_2d_tab(value);
		return (1);
	}
	scene->cylinder[i].normal_x = ft_atof(value[0]);
	scene->cylinder[i].normal_y = ft_atof(value[1]);
	scene->cylinder[i].normal_z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	if (verif_fvalue(-1, 1, scene->cylinder[i].normal_x)
		|| verif_fvalue(-1, 1, scene->cylinder[i].normal_y)
		|| verif_fvalue(-1, 1, scene->cylinder[i].normal_z))
		return (1);
	if (verfi_float(args[3]))
		return (1);
	scene->cylinder[i].d = ft_atof(args[3]);
	if (verfi_float(args[4]))
		return (1);
	scene->cylinder[i].height = ft_atof(args[4]);
	value = ft_split(args[5], ",");
	if (!value)
		return (1);
	if (verif_int(value[0], "255") || verif_int(value[1], "255")
		|| verif_int(value[2], "255"))
	{
		ft_free_2d_tab(value);
		return (1);
	}
	scene->cylinder[i].r = ft_atoi(value[0]);
	scene->cylinder[i].g = ft_atoi(value[1]);
	scene->cylinder[i].b = ft_atoi(value[2]);
	scene->cylinder[i].isset = true;
	ft_free_2d_tab(value);
	i++;
	return (0);
}
