/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:14:41 by nrolland          #+#    #+#             */
/*   Updated: 2025/07/08 17:00:13 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	check_args(t_data *data, char **args)
{
	if (!ft_strcmp(args[0], "A"))
		return (parse_ambient_light(&data->scene, args));
	else if (!ft_strcmp(args[0], "C"))
		return (parse_camera(&data->scene, args));
	else if (!ft_strcmp(args[0], "L"))
		return (parse_light(&data->scene, args));
	else if (!ft_strcmp(args[0], "sp"))
		return (parse_sphere(&data->scene, args));
	else if (!ft_strcmp(args[0], "pl"))
		return (parse_plane(&data->scene, args));
	else if (!ft_strcmp(args[0], "cy"))
		return (parse_cylinder(&data->scene, args));
	else if (!ft_strcmp(args[0], "tr"))
		return (parse_triangle(&data->scene, args));
	else if (!args || !*args || args[0][0] == '#')
		return (0);
	return (1);
}

int	creat_scene(t_data *data, int fd)
{
	char	*line;
	char	**args;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		args = ft_split(line, " \t\n\v\f\r");
		if (!args)
			return (1);
		free(line);
		if (check_args(data, args))
		{
			ft_putstr_fd("Error\nInvalid arguments in .rt file\n", 2);
			ft_lstclear(&data->scene.light, free);
			ft_lstclear(&data->scene.cylinder, free);
			ft_lstclear(&data->scene.plane, free);
			ft_lstclear(&data->scene.sphere, free);
			ft_free_2d_tab((void **)args);
			return (1);
		}
		ft_free_2d_tab((void **)args);
	}
	return (0);
}
