/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ellipsoid_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:57:13 by star              #+#    #+#             */
/*   Updated: 2025/10/01 19:21:14 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	init_elli_mat(t_ellipsoid *e)
{
	t_matrix	tr;
	t_matrix	s;
	t_matrix	r;
	t_matrix	s_inv;
	t_matrix	r_inv;

	tr = mat4_translation(e->coordinate.x, e->coordinate.y, e->coordinate.z);
	s = mat4_scale(e->scale.x, e->scale.y, e->scale.z);
	r = mul_mat4(mul_mat4(mat4_rotation_z(e->rotation.z),
				mat4_rotation_y(e->rotation.y)),
			mat4_rotation_x(e->rotation.x));
	e->tran = mul_mat4(tr, mul_mat4(r, s));
	s_inv = mat4_scale(1.0 / e->scale.x, 1.0 / e->scale.y, 1.0 / e->scale.z);
	r_inv = mul_mat4(mat4_rotation_x(-e->rotation.x),
			mul_mat4(mat4_rotation_y(-e->rotation.y),
				mat4_rotation_z(-e->rotation.z)));
	e->t_inv = mul_mat4(s_inv, mul_mat4(r_inv,
				mat4_translation(-e->coordinate.x,
					-e->coordinate.y, -e->coordinate.z)));
	e->t_inv_t = mul_mat4(mat4_transpose(r_inv), mat4_transpose(s_inv));
}

static int	init_elli_color(t_ellipsoid *ellipsoid, char **args)
{
	char	**v;

	v = ft_split(args[5], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255", 3) || verif_int(v[1], "255", 3)
		|| verif_int(v[2], "255", 3) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	ellipsoid->color = (mlx_color)
	{{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
	if (!args[6])
		return (0);
	if (verif_int(args[6], "1", 1) || args[7])
		return (1);
	ellipsoid->mat = ft_atoi(args[6]);
	return (0);
}

static int	init_ellipsoid(t_ellipsoid *e, char **args)
{
	char	**v;

	v = ft_split(args[3], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1]) || verfi_float(v[2]) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	e->scale = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	if (verfi_float(args[4]))
		return (1);
	e->size = ft_atof(args[4]) / 2;
	return (0);
}

static int	init_co_elli(t_ellipsoid *e, char **args)
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
	e->coordinate = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	v = ft_split(args[2], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1]) || verfi_float(v[2]) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	e->rotation = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	ft_free_2d_tab((void **)v);
	return (0);
}

int	parse_ellipsoid(t_scene *scene, char **args)
{
	t_ellipsoid	*ellipsoid;

	ellipsoid = malloc(sizeof(t_ellipsoid));
	if (!ellipsoid)
		return (1);
	if (init_co_elli(ellipsoid, args) || init_ellipsoid(ellipsoid, args)
		|| init_elli_color(ellipsoid, args))
	{
		free(ellipsoid);
		return (1);
	}
	if (ellipsoid->scale.x < 0.1)
		ellipsoid->scale.x = 0.1;
	if (ellipsoid->scale.y < 0.1)
		ellipsoid->scale.y = 0.1;
	if (ellipsoid->scale.z < 0.1)
		ellipsoid->scale.z = 0.1;
	init_elli_mat(ellipsoid);
	ft_lstadd_back(&scene->ellipsoid, ft_lstnew(ellipsoid));
	return (0);
}
