/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:14:41 by nrolland          #+#    #+#             */
/*   Updated: 2025/10/08 13:17:56 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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
	else if (!ft_strcmp(args[0], "el"))
		return (parse_ellipsoid(&data->scene, args));
	else if (!args || !*args || args[0][0] == '#')
		return (0);
	return (1);
}

static void	clear(t_data *d, char **args)
{
	t_list		*tmp;
	t_sphere	*sphere;

	ft_putstr_fd("Error\nInvalid arguments in .rt file\n", 2);
	tmp = d->scene.sphere;
	while (tmp)
	{
		sphere = (t_sphere *)tmp->content;
		if (sphere->tex.name)
			free(sphere->tex.name);
		if (sphere->tex.n_name)
			free(sphere->tex.n_name);
		if (sphere->tex.h_name)
			free(sphere->tex.h_name);
		tmp = tmp->next;
	}
	ft_lstclear(&d->scene.light, free);
	ft_lstclear(&d->scene.cylinder, free);
	ft_lstclear(&d->scene.plane, free);
	ft_lstclear(&d->scene.sphere, free);
	ft_lstclear(&d->scene.ellipsoid, free);
	ft_lstclear(&d->scene.triangle, free);
	ft_free_2d_tab((void **)args);
	get_next_line(-1);
}

int	creat_scene(t_data *data, int fd)
{
	int		i;
	char	*line;
	char	**args;

	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		args = ft_split(line, " \t\n\v\f\r");
		if (!args)
			return (i);
		free(line);
		if (check_args(data, args))
		{
			clear(data, args);
			return (i);
		}
		ft_free_2d_tab((void **)args);
		i++;
	}
	return (0);
}
