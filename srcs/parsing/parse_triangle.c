/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:35:50 by star              #+#    #+#             */
/*   Updated: 2025/07/25 20:25:24 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_tri_color(t_triangle *triangle, char **args)
{
	char	**v;

	v = ft_split(args[4], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255") || verif_int(v[1], "255")
		|| verif_int(v[2], "255") || v[3] || args[5])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	triangle->color = (mlx_color)
	{{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	return (0);
}

static int	init_triangle(t_triangle *triangle, char **args)
{
	char	**v;

	v = ft_split(args[2], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1]) || verfi_float(v[2]) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	triangle->b = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	v = ft_split(args[3], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1]) || verfi_float(v[2]) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	triangle->c = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	return (0);
}

static int	init_a_tri(t_triangle *t, char **args)
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
	t->a = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	return (0);
}

int	parse_triangle(t_scene *scene, char **args)
{
	t_triangle	*triangle;

	triangle = malloc(sizeof(t_triangle));
	if (!triangle)
		return (1);
	if (init_a_tri(triangle, args) || init_triangle(triangle, args)
		|| init_tri_color(triangle, args))
	{
		free(triangle);
		return (1);
	}
	triangle->normal = get_triangle_normal(triangle);
	ft_lstadd_back(&scene->triangle, ft_lstnew(triangle));
	return (0);
}
