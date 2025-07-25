/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:14:55 by nrolland          #+#    #+#             */
/*   Updated: 2025/07/25 19:21:40 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	verif_file(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (ft_isascii(str[i]) && str[i] != '.')
		i++;
	if (ft_strncmp(".jpg\0", str + i, 5)
		&& ft_strncmp(".png\0", str + i, 5)
		&& ft_strncmp(".bmp\0", str + i, 5))
		return (1);
	if (access(str, F_OK) == -1)
		return (1);
	return (0);
}

static int	init_sphere(t_sphere *sphere, char **args)
{
	char	**v;

	if (verfi_float(args[2]))
		return (1);
	sphere->diameter = ft_atof(args[2]);
	sphere->radius = sphere->diameter / 2;
	if (sphere->radius <= 0.01)
		sphere->radius = 0.01;
	v = ft_split(args[3], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255") || verif_int(v[1], "255")
		|| verif_int(v[2], "255") || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	sphere->color = (mlx_color)
	{{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	if (verif_int(args[4], "1"))
		return (1);
	sphere->tex.is_texture = ft_atoi(args[4]);
	if (verif_file(args[5]) || args[6])
		return (1);
	sphere->tex.name = ft_strdup(args[5]);
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
