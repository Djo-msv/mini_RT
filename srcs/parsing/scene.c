#include "miniRT.h"

void	check_args(t_data *data, char **args)
{
	if (!ft_strcmp(args[0], "A"))
		pars_ambient_light(&data->scene, args);
	if (!ft_strcmp(args[0], "C"))
		pars_camera(&data->scene, args);
	if (!ft_strcmp(args[0], "L"))
		pars_light(&data->scene, args);
	if (!ft_strcmp(args[0], "sp"))
		pars_sphere(&data->scene, args);
	if (!ft_strcmp(args[0], "pl"))
		pars_plane(&data->scene, args);
	if (!ft_strcmp(args[0], "cy"))
		pars_cylinder(&data->scene, args);
	
}

void	creat_scene(t_data *data, int fd)
{
	char *line;
	char **args;

	ft_memset(data->scene.light, 0, sizeof(data->scene.light));
	ft_memset(data->scene.sphere, 0, sizeof(data->scene.sphere));
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		args = ft_split(line, " \t\n");
		free(line);
		//if !args perror et exit
		check_args(data, args);
		ft_free_2d_tab((void **)args);
	}
}
