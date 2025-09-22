/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:03:03 by star              #+#    #+#             */
/*   Updated: 2025/09/22 17:31:35 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	calculate_ray_direction(t_setting_cam *scene)
{
	int		x;
	int		y;
	t_vec	pixel_center;

	x = 0;
	while (x != scene->width)
	{
		y = 0;
		while (y != scene->height)
		{
			pixel_center = vec_add(
					vec_add(scene->pixel00_loc, vec_mul(scene->pixel_delta_h,
							(scene->width - 1 - x))),
					vec_mul(scene->pixel_delta_v, (scene->height - 1 - y)));
			scene->ray_direction[x][y] = vec_sub(pixel_center,
					scene->camera_center);
			y++;
		}
		x++;
	}
}

int	alloc_ray_direction(t_setting_cam *scene)
{
	int		x;

	x = 0;
	scene->ray_direction = ft_calloc((MAX_RES_H + 1), sizeof(t_vec *));
	if (!scene->ray_direction)
		return (1);
	scene->ray_direction[(int)scene->width] = NULL;
	while (x != scene->width)
	{
		scene->ray_direction[x] = malloc(MAX_RES_W * sizeof(t_vec));
		if (!scene->ray_direction[x])
		{
			while (--x > 0)
				free(scene->ray_direction[x]);
			free(scene->ray_direction);
			return (1);
		}
		x++;
	}
	return (0);
}

void	calcule_res(t_data *data, t_setting_cam *cam)
{
	t_vec	viewport_center;
	t_vec	half_h;
	t_vec	half_v;
	t_vec	half_delta_v;
	t_vec	half_delta_h;

	viewport_center = vec_add(
			cam->camera_center,
			vec_scale(cam->forward, cam->focal_length));
	half_h = vec_scale(cam->viewport_h, 0.5);
	half_v = vec_scale(cam->viewport_v, 0.5);
	cam->viewport_upper_left = vec_sub(
			vec_sub(viewport_center, half_h),
			half_v);
	cam->pixel_delta_h = vec_scale(cam->viewport_h, 1.0f / cam->width);
	cam->pixel_delta_v = vec_scale(cam->viewport_v, 1.0f / cam->height);
	half_delta_h = vec_scale(cam->pixel_delta_h, 0.5f);
	half_delta_v = vec_scale(cam->pixel_delta_v, 0.5f);
	cam->pixel00_loc = vec_add(
			vec_add(cam->viewport_upper_left, half_delta_h),
			half_delta_v);
	cam->res_h = length(cam->pixel_delta_h) * data->image.resolution;
	cam->res_v = length(cam->pixel_delta_v) * data->image.resolution;
}

void	calcule_scene(t_data *data, t_setting_cam *scene)
{
	scene->ratio = (float)data->mlx.info.width / data->mlx.info.height;
	scene->width = data->mlx.info.width;
	scene->height = data->mlx.info.height;
	scene->focal_length = 1.0f;
	scene->viewport_height = 2.0 * tan((data->scene.camera.fov
				* M_PI / 180.0) / 2.0);
	scene->viewport_width = scene->viewport_height * scene->ratio;
}

int	setup_camera_setting(t_data *data)
{
	t_setting_cam	*scene;

	scene = &data->setting_cam;
	scene->pitch = asin(data->scene.camera.orientation.y);
	scene->yaw = atan2(data->scene.camera.orientation.x,
			data->scene.camera.orientation.z);
	scene->camera_center = data->scene.camera.coordinate;
	calcule_scene(data, scene);
	angle_camera(data, scene->pitch, scene->yaw);
	calcule_res(data, scene);
	if (alloc_ray_direction(scene))
		return (1);
	calculate_ray_direction(scene);
	return (0);
}
