/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere_a_light.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:14:55 by nrolland          #+#    #+#             */
/*   Updated: 2025/07/28 19:48:54 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient_light(t_scene *scene, char **args)
{
	char		**value;
	static int	verif = 0;

	if (verif++)
		return (1);
	if (verfi_float(args[1]))
		return (1);
	scene->a_light.ratio = ft_atof(args[1]);
	if (verif_fvalue(0.0, 1.0, scene->a_light.ratio))
		return (1);
	value = ft_split(args[2], ",");
	if (!value)
		return (1);
	if (verif_int(value[0], "255") || verif_int(value[1], "255")
		|| verif_int(value[2], "255") || value[3] || args[3])
	{
		ft_free_2d_tab((void **)value);
		return (1);
	}
	scene->a_light.color.r = ft_atoi(value[0]);
	scene->a_light.color.g = ft_atoi(value[1]);
	scene->a_light.color.b = ft_atoi(value[2]);
	scene->a_light.color.a = 255;
	ft_free_2d_tab((void **)value);
	return (0);
}

static int	init_sphere(t_sphere *sphere, char **args)
{
	char	**v;

	v = ft_split(args[3], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255") || verif_int(v[1], "255")
		|| verif_int(v[2], "255") || v[3] || args[4])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	sphere->color = (mlx_color)
	{{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	return (0);
}

static int	init_co_sphere(t_sphere *s, char **args)
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
	s->coordinate = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	if (verfi_float(args[2]))
		return (1);
	s->diameter = ft_atof(args[2]);
	s->radius = s->diameter / 2;
	if (s->radius <= 0.01)
		s->radius = 0.01;
	return (0);
}

int	parse_sphere(t_scene *scene, char **args)
{
	t_sphere	*sphere;
	static int	verif = 0;

	if (verif++)
		return (1);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (1);
	if (init_co_sphere(sphere, args) || init_sphere(sphere, args))
	{
		free(sphere);
		return (1);
	}
	ft_lstadd_back(&scene->sphere, ft_lstnew(sphere));
	return (0);
}
