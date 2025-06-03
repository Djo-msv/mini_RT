/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:09:34 by nrolland          #+#    #+#             */
/*   Updated: 2025/06/03 16:33:07 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_d_h_rgb_cylinder(t_cylinder *cylinder, char **args)
{
	char	**v;

	if (verfi_float(args[3]))
		return (1);
	cylinder->diameter = ft_atof(args[3]);
	cylinder->radius = cylinder->diameter / 2;
	if (verfi_float(args[4]))
		return (1);
	cylinder->height = ft_atof(args[4]);
	v = ft_split(args[5], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255") || verif_int(v[1], "255")
		|| verif_int(v[2], "255"))
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	cylinder->color = (t_color){ft_atoi(v[0]), ft_atoi(v[1]), ft_atoi(v[2])};
	ft_free_2d_tab((void **)v);
	return (0);
}

static int	init_normal_cylinder(t_cylinder *cylinder, char **args)
{
	char	**v;

	v = ft_split(args[2], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1])
		|| verfi_float(v[2]))
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	cylinder->normal = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	if (verif_fvalue(-1, 1, cylinder->normal.i)
		|| verif_fvalue(-1, 1, cylinder->normal.j)
		|| verif_fvalue(-1, 1, cylinder->normal.k))
		return (1);
	return (0);
}

int	parse_cylinder(t_scene *scene, char **args)
{
	char		**v;
	t_cylinder	*cylinder;

	v = ft_split(args[1], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1])
		|| verfi_float(v[2]))
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	cylinder = malloc(sizeof(t_cylinder));
	cylinder->coordinate = (t_coordinate)
	{ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	if (init_normal_cylinder(cylinder, args)
		|| init_d_h_rgb_cylinder(cylinder, args)
		|| ft_lstadd_back(&scene->cylinder, ft_lstnew(cylinder)))
	{
		free(cylinder);
		return (1);
	}
	return (0);
}
