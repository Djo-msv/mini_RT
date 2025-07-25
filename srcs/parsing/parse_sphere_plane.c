/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:14:55 by nrolland          #+#    #+#             */
/*   Updated: 2025/07/09 15:37:44 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_sphere(t_sphere *sphere, char **args)
{
	char	**v;

	if (verfi_float(args[2]))
		return (1);
	sphere->diameter = ft_atof(args[2]);
	sphere->radius = sphere->diameter / 2;
	v = ft_split(args[3], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255") || verif_int(v[1], "255")
		|| verif_int(v[2], "255") || v[3] || args[4])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	sphere->color = (mlx_color){{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
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
	if (verfi_float(v[0]) || verfi_float(v[1]) || verfi_float(v[2]) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (1);
	sphere->coordinate = (t_vec)
	{ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
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

	if (verif_fvalue(-1, 1, plane->normal.x)
		|| verif_fvalue(-1, 1, plane->normal.y)
		|| verif_fvalue(-1, 1, plane->normal.z))
		return (1);
	v = ft_split(args[3], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255") || verif_int(v[1], "255")
		|| verif_int(v[2], "255") || v[3] || args[4])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	plane->color = (mlx_color){{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	return (0);
}

static int	init_normal_plane(t_plane *plane, char **args)
{
	char	**v;

	v = ft_split(args[2], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1])
		|| verfi_float(v[2]) || v[3])
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
	char	**v;
	t_plane	*plane;

	v = ft_split(args[1], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1])
		|| verfi_float(v[2]) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (1);
	plane->coordinate = (t_vec)
	{ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	if (init_normal_plane(plane, args) || init_rgb_plane(plane, args))
	{
		free(plane);
		return (1);
	}
	ft_lstadd_back(&scene->plane, ft_lstnew(plane));
	return (0);
}
