/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam_light_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:02:13 by star              #+#    #+#             */
/*   Updated: 2025/10/01 19:21:14 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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
	if (verif_int(args[3], "180", 3) || args[4])
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

static int	init_light(t_light *l, char **args)
{
	char	**v;

	if (verfi_float(args[2]))
		return (1);
	l->brightness = ft_atof(args[2]);
	if (verif_fvalue(0, 1, l->brightness))
		return (1);
	v = ft_split(args[3], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255", 3) || verif_int(v[1], "255", 3)
		|| verif_int(v[2], "255", 3) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	l->color = (mlx_color){{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	if (!args[4])
		return (0);
	if (verfi_float(args[4]))
		return (1);
	l->size = ft_atof(args[4]);
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
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (1);
	light->size = 3;
	if (init_co_light(light, args) || init_light(light, args))
	{
		free(light);
		return (1);
	}
	ft_lstadd_back(&scene->light, ft_lstnew(light));
	return (0);
}
