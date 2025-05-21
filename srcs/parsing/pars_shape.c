#include "miniRT.h"

// int	verif_value(char *str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i] && str[i] == 0)
// 		i++;
// 	j = ft_strlen(str + i);
// 	if (j < 3)
// 		return (0);
// 	if (j > 3)
// 		return (1);
// 	if (ft_strncmp(&str[i], "1.0", j) > 0)
// 		return (1);
// 	return (0);
// }

int	pars_sphere(t_scene *scene, char **args)
{
	static int	i = 0;
	char **value;

	value = ft_split(args[1], ",");
	if (!value)
		return (1);
//	chek cordonate
	scene->sphere[i].x = ft_atof(value[0]);
	scene->sphere[i].y = ft_atof(value[1]);
	scene->sphere[i].z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	scene->sphere[i].d = ft_atof(args[2]);
	value = ft_split(args[3], ",");
	if (!value)
		return (1);
//	chek cordonate
	scene->sphere[i].r = ft_atoi(value[0]);
	scene->sphere[i].g = ft_atoi(value[1]);
	scene->sphere[i].b = ft_atoi(value[2]);
	scene->sphere[i].isset = true;
	ft_free_2d_tab(value);
	i++;
	return (0);
}

int	pars_plane(t_scene *scene, char **args)
{
	static int	i = 0;
	char **value;

	value = ft_split(args[1], ",");
	if (!value)
		return (1);
//	chek cordonate
	scene->plane[i].x = ft_atof(value[0]);
	scene->plane[i].y = ft_atof(value[1]);
	scene->plane[i].z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	value = ft_split(args[2], ",");
	if (!value)
		return (1);
//	chek cordonate
	scene->plane[i].normal_x = ft_atof(value[0]);
	scene->plane[i].normal_y = ft_atof(value[1]);
	scene->plane[i].normal_z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	value = ft_split(args[3], ",");
	if (!value)
		return (1);
//	chek cordonate
	scene->plane[i].r = ft_atoi(value[0]);
	scene->plane[i].g = ft_atoi(value[1]);
	scene->plane[i].b = ft_atoi(value[2]);
	scene->plane[i].isset = true;
	ft_free_2d_tab(value);
	i++;
	return (0);
}

int	pars_cylinder(t_scene *scene, char **args)
{
	static int	i = 0;
	char **value;

	value = ft_split(args[1], ",");
	if (!value)
		return (1);
//	chek cordonate
	scene->cylinder[i].x = ft_atof(value[0]);
	scene->cylinder[i].y = ft_atof(value[1]);
	scene->cylinder[i].z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	value = ft_split(args[2], ",");
	if (!value)
		return (1);
//	chek cordonate
	scene->cylinder[i].normal_x = ft_atof(value[0]);
	scene->cylinder[i].normal_y = ft_atof(value[1]);
	scene->cylinder[i].normal_z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	scene->cylinder[i].d = ft_atof(args[3]);
	scene->cylinder[i].height = ft_atof(args[4]);
	value = ft_split(args[5], ",");
	if (!value)
		return (1);
//	chek cordonate
	scene->cylinder[i].r = ft_atoi(value[0]);
	scene->cylinder[i].g = ft_atoi(value[1]);
	scene->cylinder[i].b = ft_atoi(value[2]);
	scene->cylinder[i].isset = true;
	ft_free_2d_tab(value);
	i++;
	return (0);
}
