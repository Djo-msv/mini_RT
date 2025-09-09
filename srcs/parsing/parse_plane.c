/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:27:22 by star              #+#    #+#             */
/*   Updated: 2025/09/09 18:54:16 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_checkerboard_pattern(t_plane *plane, char **args)
{
	char	**v;

	plane->l_x_pattern = ft_atof(args[4]);
	if (verfi_float(args[5]))
		return (1);
	plane->l_z_pattern = ft_atof(args[5]);
	v = ft_split(args[6], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255", 3) || verif_int(v[1], "255", 3)
		|| verif_int(v[2], "255", 3) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	plane->pattern_color = (mlx_color)
	{{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	if (!args[7])
		return (0);
	if (verif_int(args[7], "3", 1) || args[8])
		return (1);
	plane->mat = ft_atoi(args[7]);
	return (0);
}

static int	pars_number(t_plane *plane, char **args)
{
	if (!args[4])
		return (0);
	if (!args[5])
	{
		if (verif_int(args[4], "1", 1))
			return (1);
		plane->mat = ft_atoi(args[4]);
		return (0);
	}
	plane->is_pattern = 1;
	if (verfi_float(args[4]))
		return (1);
	if (init_checkerboard_pattern(plane, args))
		return (1);
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
	if (verif_int(v[0], "255", 3) || verif_int(v[1], "255", 3)
		|| verif_int(v[2], "255", 3) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	plane->color = (mlx_color)
	{{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	if (pars_number(plane, args))
		return (1);
	return (0);
}

static int	init_normal_plane(t_plane *p, char **args)
{
	char	**v;

	v = ft_split(args[1], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1])
		|| verfi_float(v[2]) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	p->coordinate = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	v = ft_split(args[2], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1])
		|| verfi_float(v[2]) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	p->normal = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	return (0);
}

int	parse_plane(t_scene *scene, char **args)
{
	t_plane	*p;

	p = malloc(sizeof(t_plane));
	if (!p)
		return (1);	
	p->is_pattern = 0;
	p->mat = 0;
	if (init_normal_plane(p, args) || init_rgb_plane(p, args))
	{
		free(p);
		return (1);
	}
	ft_lstadd_back(&scene->plane, ft_lstnew(p));
	return (0);
}
