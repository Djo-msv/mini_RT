/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ellipsoid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:57:13 by star              #+#    #+#             */
/*   Updated: 2025/07/12 17:51:51 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	ellipsoid->normal = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	v = ft_split(args[3], ",");
	if (!v)
		return (1);
	if (verfi_float(v[0]) || verfi_float(v[1]) || verfi_float(v[2]) || v[3])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	ellipsoid->scale = (t_vec){ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2])};
	v = ft_split(args[4], ",");
	if (!v)
		return (1);
	if (verif_int(v[0], "255") || verif_int(v[1], "255")
		|| verif_int(v[2], "255") || v[3] || args[5])
	{
		ft_free_2d_tab((void **)v);
		return (1);
	}
	ellipsoid->color = (mlx_color){{255, ft_atoi(v[2]), ft_atoi(v[1]), ft_atoi(v[0])}};
	ft_free_2d_tab((void **)v);
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
	if (init_ellipsoid(ellipsoid, args))
	{
		free(ellipsoid);
		return (1);
	}
	t_matrix	tr;
	t_matrix	ro;
	t_matrix	s;

	tr = mat4_translation(ellipsoid->coordinate.x, ellipsoid->coordinate.y, ellipsoid->coordinate.z);
	ro = mul_mat4(mat4_rotation_z(ellipsoid->normal.z), mul_mat4(mat4_rotation_y(ellipsoid->normal.y), mat4_rotation_x(ellipsoid->normal.x)));
	s = mat4_scale(ellipsoid->scale.x, ellipsoid->scale.y, ellipsoid->scale.z);
	ellipsoid->tran = mul_mat4(tr, mul_mat4(ro, s));
	ellipsoid->t_inv = mat4_inverse(ellipsoid->tran);
	ellipsoid->t_inv_t = mat4_transpose(ellipsoid->t_inv);
	ft_lstadd_back(&scene->ellipsoid, ft_lstnew(ellipsoid));
	return (0);
}
