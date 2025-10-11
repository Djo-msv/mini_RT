/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:14:55 by nrolland          #+#    #+#             */
/*   Updated: 2025/10/11 15:57:09 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static int	assign_tex(t_sphere *sphere, char **args, int i, int type)
{
	if (verif_file(args[i]))
		return (1);
	if (type == 0)
	{
		sphere->tex.name = ft_strdup(args[i]);
		sphere->tex.is_texture = 1;
	}
	if (type == 1)
	{
		sphere->tex.n_name = ft_strdup(args[i]);
		sphere->tex.is_normal = 1;
	}
	if (type >= 2)
		return (1);
	return (0);
}

static int	init_texture(t_sphere *sphere, char **args)
{
	int	i;
	int	type;

	i = 4;
	type = 0;
	while (args[i])
	{
		if (!verif_int(args[i], "1", 1) && ft_atoi(args[i]) == 1)
			i++;
		else if (!verif_int(args[i], "1", 1) && ft_atoi(args[i]) == 0 && type != 3)
		{
			i++;
			type++;
			continue ;
		}
		if (!args[i])
		{
			sphere->mat = 1;
			return (0);
		}
		if (assign_tex(sphere, args, i, type++))
			return (1);
		i++;
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

	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (1);
	sphere->mat = 0;
	sphere->tex.name = NULL;
	sphere->tex.n_name = NULL;
	if (init_co_sphere(sphere, args) || init_sphere(sphere, args)
		|| init_texture(sphere, args))
	{
		free(sphere);
		return (1);
	}
	ft_lstadd_back(&scene->sphere, ft_lstnew(sphere));
	return (0);
}
