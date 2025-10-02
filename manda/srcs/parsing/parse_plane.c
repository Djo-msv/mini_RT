/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:27:22 by star              #+#    #+#             */
/*   Updated: 2025/10/02 17:32:02 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	plane->color = (mlx_color)
	{{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	if (plane->normal.x == 0 && plane->normal.y == 0 && plane->normal.z == 0)
		plane->normal = (t_vec){0, 1, 0};
	plane->normal = normalize(plane->normal);
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
	t_plane		*p;

	p = malloc(sizeof(t_plane));
	if (!p)
		return (1);
	if (init_normal_plane(p, args) || init_rgb_plane(p, args))
	{
		free(p);
		return (1);
	}
	ft_lstadd_back(&scene->plane, ft_lstnew(p));
	return (0);
}
