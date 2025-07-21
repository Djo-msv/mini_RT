/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:27:22 by star              #+#    #+#             */
/*   Updated: 2025/07/21 20:28:54 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_checkerboard_pattern(t_plane *plane, char **args)
{
	char	**v;

	if (verfi_float(args[5]))
		return (1);
	plane->l_x_pattern = ft_atof(args[5]);	
	if (verfi_float(args[6]))
		return (1);
	plane->l_z_pattern = ft_atof(args[6]);
	v = ft_split(args[7], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255") || verif_int(v[1], "255")
		|| verif_int(v[2], "255") || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	plane->pattern_color = (mlx_color)
	{{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	if (verif_int(args[8], "1") || args[9])
		return (1);
	plane->mat = ft_atoi(args[8]);
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
		|| verif_int(v[2], "255") || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	plane->color = (mlx_color)
	{{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	if (verif_int(args[4], "1"))
		return (1);
	plane->is_pattern = ft_atoi(args[4]);
	if (init_checkerboard_pattern(plane, args))
		return (1);
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
