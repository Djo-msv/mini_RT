/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ellipsoid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:57:13 by star              #+#    #+#             */
/*   Updated: 2025/07/21 19:01:54 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_elli_mat(t_ellipsoid *ellipsoid)
{
	t_matrix	tr;
	t_matrix	s;
	t_matrix	s_inv;
	t_matrix	tr_inv;

	tr = mat4_translation(ellipsoid->coordinate.x,
			ellipsoid->coordinate.y, ellipsoid->coordinate.z);
	s = mat4_scale(ellipsoid->scale.x, ellipsoid->scale.y, ellipsoid->scale.z);
	ellipsoid->tran = mul_mat4(tr, s);
	s_inv = mat4_scale(1.0 / ellipsoid->scale.x, 1.0
			/ ellipsoid->scale.y, 1.0 / ellipsoid->scale.z);
	tr_inv = mat4_translation(-ellipsoid->coordinate.x,
			-ellipsoid->coordinate.y, -ellipsoid->coordinate.z);
	ellipsoid->t_inv = mul_mat4(s_inv, tr_inv);
	ellipsoid->t_inv_t = mat4_transpose(ellipsoid->t_inv);
}

static int	init_elli_color(t_ellipsoid *ellipsoid, char **args)
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
	ellipsoid->color = (mlx_color)
	{{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	return (0);
}

static int	init_ellipsoid(t_ellipsoid *ellipsoid, char **args)
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
	ellipsoid->scale = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	if (verfi_float(args[3]))
		return (1);
	ellipsoid->size = ft_atof(args[3]) / 2;
	return (0);
}

int	parse_ellipsoid(t_scene *scene, char **args)
{
	char		**v;
	t_ellipsoid	*ellipsoid;

	v = ft_split(args[1], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1]) || verfi_float(v[2]) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	ellipsoid = malloc(sizeof(t_ellipsoid));
	if (!ellipsoid)
		return (1);
	ellipsoid->coordinate = (t_vec)
	{ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	if (init_ellipsoid(ellipsoid, args) || init_elli_color(ellipsoid, args))
	{
		free(ellipsoid);
		return (1);
	}
	init_elli_mat(ellipsoid);
	ft_lstadd_back(&scene->ellipsoid, ft_lstnew(ellipsoid));
	return (0);
}
