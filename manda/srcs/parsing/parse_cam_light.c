/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:02:13 by star              #+#    #+#             */
/*   Updated: 2025/07/30 16:40:02 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_cam(t_scene *scene, char **args)
{
	char	**value;

	value = ft_split(args[2], ",");
	if (!value)
		return (1);
	if (verfi_float(value[0]) || verfi_float(value[1])
		|| verfi_float(value[2]) || value[3])
	{
		ft_free_2d_tab((void **)value);
		return (1);
	}
	scene->camera.orientation.x = ft_atof(value[0]);
	scene->camera.orientation.y = ft_atof(value[1]);
	scene->camera.orientation.z = ft_atof(value[2]);
	ft_free_2d_tab((void **)value);
	if (verif_fvalue(-1, 1, scene->camera.orientation.x)
		|| verif_fvalue(-1, 1, scene->camera.orientation.y)
		|| verif_fvalue(-1, 1, scene->camera.orientation.z))
		return (1);
	scene->camera.orientation = normalize(scene->camera.orientation);
	if (verif_int(args[3], "180") || args[4])
		return (1);
	scene->camera.fov = ft_atof(args[3]);
	return (0);
}

int	parse_camera(t_scene *scene, char **args)
{
	char		**value;
	static int	verif = 0;

	if (verif++)
		return (1);
	if (!args[1])
		return (1);
	scene->camera.is_cam = 1;
	value = ft_split(args[1], ",");
	if (!value)
		return (1);
	if (verfi_float(value[0]) || verfi_float(value[1])
		|| verfi_float(value[2]) || value[3])
	{
		ft_free_2d_tab((void **)value);
		return (1);
	}
	scene->camera.coordinate.x = ft_atof(value[0]);
	scene->camera.coordinate.y = ft_atof(value[1]);
	scene->camera.coordinate.z = ft_atof(value[2]);
	ft_free_2d_tab((void **)value);
	if (init_cam(scene, args))
		return (1);
	return (0);
}

static int	init_light(t_light *light, char **args)
{
	char		**value;

	if (verfi_float(args[2]))
		return (1);
	light->brightness = ft_atof(args[2]);
	if (verif_fvalue(0, 1, light->brightness))
		return (1);
	value = ft_split(args[3], ",");
	if (!value)
		return (1);
	if (verif_int(value[0], "255") || verif_int(value[1], "255")
		|| verif_int(value[2], "255") || value[3] || args[4])
	{
		ft_free_2d_tab((void **)value);
		return (1);
	}
	light->color.r = ft_atoi(value[0]);
	light->color.g = ft_atoi(value[1]);
	light->color.b = ft_atoi(value[2]);
	light->color.a = 255;
	ft_free_2d_tab((void **)value);
	return (0);
}

static int	init_co_light(t_light *l, char **args)
{
	char		**v;

	v = ft_split(args[1], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1]) || verfi_float(v[2]) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	l->coordinate = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	return (0);
}

int	parse_light(t_scene *scene, char **args)
{
	t_light		*light;
	static int	verif = 0;

	if (verif++)
		return (1);
	light = malloc(sizeof(t_light));
	if (!light)
		return (1);
	if (init_co_light(light, args) || init_light(light, args))
	{
		free(light);
		return (1);
	}
	ft_lstadd_back(&scene->light, ft_lstnew(light));
	return (0);
}
