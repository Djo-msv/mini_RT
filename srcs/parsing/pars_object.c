#include "miniRT.h"

int	pars_camera(t_scene *scene, char **args)
{
	char **value;

	if (!args[1])
		return (1);
	value = ft_split(args[1], ",");
//	chek cordonate
	scene->camera.x = ft_atof(value[0]);
	scene->camera.y = ft_atof(value[1]);
	scene->camera.z = ft_atof(value[2]);
	ft_free_2d_tab(value);

	value = ft_split(args[2], ",");
//	chek cordonate
	scene->camera.orient_x = ft_atof(value[0]);
	scene->camera.orient_y = ft_atof(value[1]);
	scene->camera.orient_z = ft_atof(value[2]);

	scene->camera.fov = ft_atof(args[3]);
	ft_free_2d_tab(value);
	return (0);
}

int	pars_ambient_light(t_scene *scene, char **args)
{
	char **value;

	if (!args[1])
		return (1);

	scene->a_light.range = ft_atof(args[1]);
	value = ft_split(args[2], ",");
//	chek cordonate
	scene->a_light.r = ft_atoi(value[0]);
	scene->a_light.g = ft_atoi(value[1]);
	scene->a_light.b = ft_atoi(value[2]);
	ft_free_2d_tab(value);

	return (0);
}

int	pars_light(t_scene *scene, char **args)
{
	static int	i = 0;
	char **value;

	value = ft_split(args[1], ",");
//	chek cordonate
	scene->light[i].x = ft_atof(value[0]);
	scene->light[i].y = ft_atof(value[1]);
	scene->light[i].z = ft_atof(value[2]);
	ft_free_2d_tab(value);

	scene->light[i].bright = ft_atof(args[2]);

	value = ft_split(args[3], ",");
//	chek cordonate
	scene->light[i].r = ft_atoi(value[0]);
	scene->light[i].g = ft_atoi(value[1]);
	scene->light[i].b = ft_atoi(value[2]);
	scene->light[i].isset = true;

	ft_free_2d_tab(value);
	i++;
	return (0);
}
