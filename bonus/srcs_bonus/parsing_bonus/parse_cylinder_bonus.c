/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:09:34 by nrolland          #+#    #+#             */
/*   Updated: 2025/09/11 17:28:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static int	init_d_h_rgb_cylinder(t_cylinder *c, char **args)
{
	char	**v;

	if (verfi_float(args[3]))
		return (1);
	c->diameter = ft_atof(args[3]);
	c->radius = c->diameter / 2;
	if (verfi_float(args[4]))
		return (1);
	c->height = ft_atof(args[4]);
	v = ft_split(args[5], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255", 3) || verif_int(v[1], "255", 3)
		|| verif_int(v[2], "255", 3) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	c->color = (mlx_color)
	{{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	if (!args[6])
		return (0);
	if (verif_int(args[6], "3", 1) || args[7])
		return (1);
	c->mat = ft_atoi(args[6]);
	return (0);
}

static int	init_normal_cylinder(t_cylinder *cy, char **args)
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
	cy->normal = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	if (verif_fvalue(-1, 1, cy->normal.x)
		|| verif_fvalue(-1, 1, cy->normal.y)
		|| verif_fvalue(-1, 1, cy->normal.z))
		return (1);
	if (cy->normal.x == 0 && cy->normal.y == 0 && cy->normal.z == 0)
		cy->normal = (t_vec){0, 0, 1};
	cy->normal = normalize(cy->normal);
	return (0);
}

static int	init_co_cy(t_cylinder *c, char **args)
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
	c->coordinate = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	return (0);
}

int	parse_cylinder(t_scene *scene, char **args)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (1);
	cylinder->mat = 0;	
	if (init_co_cy(cylinder, args) || init_normal_cylinder(cylinder, args)
		|| init_d_h_rgb_cylinder(cylinder, args)
		|| ft_lstadd_back(&scene->cylinder, ft_lstnew(cylinder)))
	{
		free(cylinder);
		return (1);
	}
	return (0);
}
