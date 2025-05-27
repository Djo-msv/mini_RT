#include "miniRT.h"

static int	check_args(t_data *data, char **args)
{

	// if (!ft_strcmp(args[0], "A"))
	// 	return (parse_ambient_light(&data->scene, args));
	// else if (!ft_strcmp(args[0], "C"))
	// 	return (parse_camera(&data->scene, args));
	if (!ft_strcmp(args[0], "L"))
		return (parse_light(&data->scene, args));
	// else if (!ft_strcmp(args[0], "sp"))
	// 	return (parse_sphere(&data->scene, args));
	// else if (!ft_strcmp(args[0], "pl"))
	// 	return (parse_plane(&data->scene, args));
	// else if (!ft_strcmp(args[0], "cy"))
	// 	return (parse_cylinder(&data->scene, args));
	else if (!args || !*args)
		return (0);
	return (0);////////////////1
}

int	creat_scene(t_data *data, int fd)
{
	char *line;
	char **args;

	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		args = ft_split(line, " \t\n\v\f\r");
		if (!args)
			return (1);
		free(line);
		if (check_args(data, args))
		{
			ft_putstr_fd("Error\nInvalid arguments in .rt file\n", 2);
			return (1);
		}
		ft_free_2d_tab((void **)args);
	}
	return (0);
}
