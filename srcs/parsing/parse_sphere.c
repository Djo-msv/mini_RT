/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:14:55 by nrolland          #+#    #+#             */
/*   Updated: 2025/09/09 18:55:48 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int assign_tex(t_sphere *sphere, char **args, int i)
{
	if (verif_file(args[i]))
		return (1);
	if (sphere->tex.is_texture == 1)
	{
		sphere->tex.is_normal = 1;
		sphere->tex.n_name = ft_strdup(args[i]);
	}
	else
	{
		sphere->tex.is_texture = 1;
		sphere->tex.name = ft_strdup(args[i]);
	}
	return (0);
}

static int	init_texture(t_sphere *sphere, char **args)
{
	int	v;
	int	i;

	v = 0;
	i = 3;
	while (++i <= 8)
	{
		if (!args[i])
			return (0);
		if (args[i] && i == 8)
			return (1);
		if (!verif_int(args[i], "3", 1) && !v++)
			sphere->mat = ft_atoi(args[i]);
		else if (assign_tex(sphere, args, i))
			return (1);
	}
	return (0);
}

static int	init_sphere(t_sphere *sphere, char **args)
{
	char	**v;

	v = ft_split(args[3], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255", 3) || verif_int(v[1], "255", 3)
		|| verif_int(v[2], "255", 3) || v[3])
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

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (1);
	sphere->tex.is_texture = 0;
	sphere->tex.is_normal = 0;
	sphere->mat = 0;
	if (init_co_sphere(sphere, args) || init_sphere(sphere, args)
		|| init_texture(sphere, args))
	{
		free(sphere);
		return (1);
	}
	ft_lstadd_back(&scene->sphere, ft_lstnew(sphere));
	return (0);
}
