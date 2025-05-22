#include "miniRT.h"

int	verif_str(char *str)
{
	int	i;
	int	v;

	i = 0;
	v = 0;
	if (!str)
		return (1);
	if ((!ft_isdigit(str[i]) && str[i] != '+'))
		return (1);
	while (str[i])
	{
		if (str[i] == '.')
		{
			
			v++;
		}
		if ((!ft_isdigit(str[i]) && str[i] != '.' && str[i] != '+') || v == 2)
			return (1);
		i++;
	}
	return (0);
}

int	verif_value(char *str, char *min, char *max)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	if (verif_str(str))
		return (1);
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '.')
		i--;
	j = ft_strlen(str + i);
	len = ft_strlen(max);
	if (j > len)
		return (1);
	if (ft_strncmp(&str[i], min, j) < 0)
		return (1);
	if (ft_strncmp(&str[i], max, j) > 0)
		return (1);
	return (0);
}

int	pars_camera(t_scene *scene, char **args)
{
	char **value;

	if (!args[1])
		return (1);
	value = ft_split(args[1], ",");
	if (!value)
		return (1);
//	chek cordonate
	scene->camera.x = ft_atof(value[0]);
	scene->camera.y = ft_atof(value[1]);
	scene->camera.z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	value = ft_split(args[2], ",");
	if (!value)
		return (1);
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

	if (verif_value(args[1], "0.000000", "1.000000"))
		return (1);
	scene->a_light.range = ft_atof(args[1]);
	value = ft_split(args[2], ",");
	if (!value)
		return (1);
	if (verif_value(value[0], "0", "255"))
		return (1);
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
	if (!value)
		return (1);
//	chek cordonate
	scene->light[i].x = ft_atof(value[0]);
	scene->light[i].y = ft_atof(value[1]);
	scene->light[i].z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	scene->light[i].bright = ft_atof(args[2]);
	value = ft_split(args[3], ",");
	if (!value)
		return (1);
//	chek cordonate
	scene->light[i].r = ft_atoi(value[0]);
	scene->light[i].g = ft_atoi(value[1]);
	scene->light[i].b = ft_atoi(value[2]);
	scene->light[i].isset = true;
	ft_free_2d_tab(value);
	i++;
	return (0);
}
