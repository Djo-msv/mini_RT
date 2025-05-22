#include "miniRT.h"

static int	verif_str(char *str, int is_neg)
{
	int	i;
	int	v;

	i = 0;
	v = 0;
	if (!str)
		return (1);
	if ((!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-'))
		return (1);
	if (!is_neg && str[i] == '-')
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (!ft_isdigit(str[i - 1]) || !ft_isdigit(str[i + 1]))
				return (1);
			v++;
		}
		if ((!ft_isdigit(str[i]) && str[i] != '.') || v == 2)
			return (1);
		i++;
	}
	return (0);
}

int	verif_zero_to_max(char *str, char *min, char *max, int is_neg)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	if (verif_str(str, is_neg))
		return (1);
	if (str[i] == '+' || str[i] == '-')
			i++;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] == '.')
		i--;
	j = ft_strlen(str + i);
	len = ft_strlen(max);
	if (j > len)
		return (1);
	if (ft_strncmp(&str[i], min, j) < 0)
		return (1);
	if (ft_strncmp(&str[i], max, j) > 0)///probleme 0 255
		return (1);
	return (0);
}

int	subtraction(char *str, int len)
{
	int	i;

	i = 0;
	while (str[len] == '0')
	{
		len--;
		i++;
	}
	return (i);
}

int	verfi_neg_to_max(char *str, int	one)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (verif_str(str, 1))
		return (1);
	if (str[i] == '+' || str[i] == '-')
			i++;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] == '.')
		i--;
	j = ft_strlen(str + i);
	j = j - subtraction(&str[i], j - 1);
	if (j > 8)
		return (1);
	if (one)
	{
		if (ft_strncmp(&str[i], "1.000000", j) > 0)
			return (1);
	}
	return (0);
}

int	pars_camera(t_scene *scene, char **args)
{
	char **value;
	int	exit;

	exit = 0;
	if (!args[1])
		return (1);
	value = ft_split(args[1], ",");
	if (!value)
		return (1);
	if (verfi_neg_to_max(value[0], 0))
		exit = 1;
	else
		scene->camera.x = ft_atof(value[0]);
	if (verfi_neg_to_max(value[1], 0))
		exit = 1;
	else
		scene->camera.y = ft_atof(value[1]);
	if (verfi_neg_to_max(value[2], 0))
		exit = 1;
	else
		scene->camera.z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	value = ft_split(args[2], ",");
	if (!value)
		return (1);
	if (verfi_neg_to_max(value[0], 1))
		exit = 1;
	else
	scene->camera.orient_x = ft_atof(value[0]);
	if (verfi_neg_to_max(value[1], 1))
		exit = 1;
	else
	scene->camera.orient_y = ft_atof(value[1]);
	if (verfi_neg_to_max(value[2], 1))
		exit = 1;
	else
	scene->camera.orient_z = ft_atof(value[2]);
	// if (verif_zero_to_max(args[3], "0", "180", 0))
	// 	exit = 1;
	// else
	scene->camera.fov = ft_atof(args[3]);
	ft_free_2d_tab(value);
	return (exit);
}

int	pars_ambient_light(t_scene *scene, char **args)
{
	char **value;
	int	exit;

	exit = 0;
	if (verif_zero_to_max(args[1], "0.000000", "1.000000", 0))
		return (1);
	scene->a_light.range = ft_atof(args[1]);
	value = ft_split(args[2], ",");
	if (!value)
		return (1);
	if (verif_zero_to_max(value[0], "000", "255", 0))
		exit = 1;
	else
		scene->a_light.r = ft_atoi(value[0]);
	if (verif_zero_to_max(value[1], "000", "255", 0))
		exit = 1;
	else
		scene->a_light.g = ft_atoi(value[1]);
	if (verif_zero_to_max(value[2], "000", "255", 0))
		exit = 1;
	else
		scene->a_light.b = ft_atoi(value[2]);
	ft_free_2d_tab(value);
	return (exit);
}

int	pars_light(t_scene *scene, char **args)
{
	static int	i = 0;
	char 		**value;
	int			exit;

	exit = 0;
	value = ft_split(args[1], ",");
	if (!value)
		return (1);
	// if (verfi_neg_to_max(value[0], 0))
	// 	exit = 1;
	scene->light[i].x = ft_atof(value[0]);
	// if (verfi_neg_to_max(value[1], 0))
	// 	exit = 1;
	scene->light[i].y = ft_atof(value[1]);
	// if (verfi_neg_to_max(value[2], 0))
	// 	exit = 1;
	scene->light[i].z = ft_atof(value[2]);
	ft_free_2d_tab(value);
	// if (verif_zero_to_max(args[1], "0.000000", "1.000000", 0))
	// 	return (1);
	scene->light[i].bright = ft_atof(args[2]);
	value = ft_split(args[3], ",");
	if (!value)
		return (1);
	// if (verif_zero_to_max(value[0], "0", "255", 0))
	// 	exit = 1;
	// else
	scene->light[i].r = ft_atoi(value[0]);
	// if (verif_zero_to_max(value[1], "0", "255", 0))
	// 	exit = 1;
	// else
	scene->light[i].g = ft_atoi(value[1]);
	// if (verif_zero_to_max(value[2], "0", "255", 0))
	// 	exit = 1;
	// else
	scene->light[i].b = ft_atoi(value[2]);
	scene->light[i].isset = true;
	ft_free_2d_tab(value);
	i++;
	return (0);
}
