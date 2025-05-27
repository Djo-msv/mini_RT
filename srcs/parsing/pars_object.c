#include "miniRT.h"

// static int	init_cam(t_scene *scene, char **args)
// {
// 	char	**value;

// 	value = ft_split(args[2], ",");
// 	if (!value)
// 		return (1);
// 	if (verfi_float(value[0]) || verfi_float(value[1])
// 		|| verfi_float(value[2]))
// 	{
// 		ft_free_2d_tab((void **)value);
// 		return (1);
// 	}
// 	scene->camera.orientation.i = ft_atof(value[0]);
// 	scene->camera.orientation.j = ft_atof(value[1]);
// 	scene->camera.orientation.k = ft_atof(value[2]);
// 	ft_free_2d_tab((void **)value);
// 	if (verif_fvalue(-1, 1, scene->camera.orientation.i)
// 		|| verif_fvalue(-1, 1, scene->camera.orientation.j)
// 		|| verif_fvalue(-1, 1, scene->camera.orientation.k))
// 		return (1);
// 	if (verif_int(args[3], "180"))
// 		return (1);
// 	scene->camera.fov = ft_atof(args[3]);
// 	return (0);
// }

// int	parse_camera(t_scene *scene, char **args)
// {
// 	char **value;

// 	if (!args[1])
// 		return (1);
// 	value = ft_split(args[1], ",");
// 	if (!value)
// 		return (1);
// 	if (verfi_float(value[0]) || verfi_float(value[1])
// 		|| verfi_float(value[2]))
// 	{
// 		ft_free_2d_tab((void **)value);
// 		return (1);
// 	}
// 	scene->camera.coordinate.x = ft_atof(value[0]);
// 	scene->camera.coordinate.y = ft_atof(value[1]);
// 	scene->camera.coordinate.z = ft_atof(value[2]);
// 	ft_free_2d_tab((void **)value);
// 	if (init_cam(scene, args))
// 		return (1);
// 	return (0);
// }

// int	parse_ambient_light(t_scene *scene, char **args)
// {
// 	char **value;

// 	if (verfi_float(args[1]))
// 		return (1);
// 	scene->a_light.range = ft_atof(args[1]);
// 	if (verif_fvalue(0.0, 1.0, scene->a_light.range))
// 		return (1);
// 	value = ft_split(args[2], ",");
// 	if (!value)
// 		return (1);
// 	if (verif_int(value[0], "255") || verif_int(value[1], "255")
// 		|| verif_int(value[2], "255"))
// 	{
// 	    ft_free_2d_tab((void **)value);
// 		return (1);
// 	}
// 	scene->a_light.color.r = ft_atoi(value[0]);
// 	scene->a_light.color.g = ft_atoi(value[1]);
// 	scene->a_light.color.b = ft_atoi(value[2]);
// 	ft_free_2d_tab((void **)value);
// 	return (0);
// }

static int init_light(t_light *light, char **args)
{
	char	**value;

	if (verfi_float(args[2]))
		return (1);
	light->bright = ft_atof(args[2]);
	if (verif_fvalue(0, 1, light->bright))
		return (1);
	value = ft_split(args[3], ",");
	if (!value)
		return (1);
	if (verif_int(value[0], "255") || verif_int(value[1], "255")
		|| verif_int(value[2], "255"))
	{
		ft_free_2d_tab((void **)value);
		return (1);
	}
	light->color.r = ft_atoi(value[0]);
	light->color.g = ft_atoi(value[1]);
	light->color.b = ft_atoi(value[2]);
	ft_free_2d_tab((void **)value);
	return (0);
}

int	ft_new_alloc(t_list **lst, void *content, size_t size)
{
	t_list	*new;
	t_light	*copy;

	copy = malloc(size);
	if (!copy)
		return (1);
	copy = content;
	new = ft_lstnew(copy);
	if (!new)
	{
		free(copy);
		return (1);
	}
	ft_lstadd_back(lst, new);
	return (0);
}

int	parse_light(t_scene *scene, char **args)
{
	char 		**value;
	t_light		light;

	value = ft_split(args[1], ",");
	if (!value)
		return (1);
	if (verfi_float(value[0]) || verfi_float(value[1])
		|| verfi_float(value[2]))
	{
	    ft_free_2d_tab((void **)value);
		return (1);
	}
	light.coordinate.x = ft_atof(value[0]);
	light.coordinate.y = ft_atof(value[1]);
	light.coordinate.z = ft_atof(value[2]);
	ft_free_2d_tab((void **)value);
	if (init_light(&light, args))
		return (1);
	if (ft_new_alloc(&scene->light, &light, sizeof(t_light)))
		return (1);
	return (0);
}
