/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_a_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:04:28 by star              #+#    #+#             */
/*   Updated: 2025/09/02 19:05:30 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient_light(t_scene *scene, char **args)
{
	char		**value;
	static int	verif = 0;

	if (verif++)
		return (1);
	if (verfi_float(args[1]))
		return (1);
	scene->a_light.ratio = ft_atof(args[1]);
	if (verif_fvalue(0.0, 1.0, scene->a_light.ratio))
		return (1);
	value = ft_split(args[2], ",");
	if (!value)
		return (1);
	if (verif_int(value[0], "255", 3) || verif_int(value[1], "255", 3)
		|| verif_int(value[2], "255", 3) || value[3] || args[3])
	{
		ft_free_2d_tab((void **)value);
		return (1);
	}
	scene->a_light.color.r = ft_atoi(value[0]);
	scene->a_light.color.g = ft_atoi(value[1]);
	scene->a_light.color.b = ft_atoi(value[2]);
	scene->a_light.color.a = 255;
	ft_free_2d_tab((void **)value);
	return (0);
}
