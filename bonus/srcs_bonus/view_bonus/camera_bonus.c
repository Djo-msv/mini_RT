/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:38:23 by star              #+#    #+#             */
/*   Updated: 2025/09/17 18:57:46 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	set_camera_window(t_data *data, t_camera *cam)
{
	mlx_window_create_info	info;

	info = data->mlx.info;
	cam->d_height = 2.0f * tan(cam->fov_rad / 2.0f);
	cam->d_width = cam->d_height * ((float)info.width / (float)info.height);
}

void	set_camera_value(t_data *data, t_camera *cam)
{
	t_vec	tmp_up;

	tmp_up = (t_vec){0.0f, 1.0f, 0.0f};
	cam->move = 1;
	cam->forward = normalize(data->scene.camera.orientation);
	if (fabs(cam->forward.y) > 0.999f)
		tmp_up = (t_vec){0.0f, 0.0f, 1.0f};
	cam->right = normalize(cross(cam->forward, tmp_up));
	cam->up = cross(cam->forward, cam->right);
	cam->coordinate = data->scene.camera.coordinate;
	cam->fov_rad = (data->scene.camera.fov * M_PI) / 180;
	cam->yaw = atan2(cam->forward.x, cam->forward.z);
	cam->pitch = asin(cam->forward.y);
	set_camera_window(data, cam);
	set_camera_ray(data->pool->ray_direction, cam, data->mlx.info);
}

t_vec	calcule_ray_direction(t_camera *cam, mlx_window_create_info info,
		int x, int y)
{
	t_vec	dir;
	float	x_ray;
	float	y_ray;

	x_ray = ((x + 0.5f) / info.width - 0.5f);
	y_ray = ((y + 0.5f) / info.height - 0.5f);
	dir = vec_add(
			vec_add(cam->forward, vec_mul(cam->right, x_ray * cam->d_width)),
			vec_mul(cam->up, y_ray * cam->d_height));
	return (dir);
}

void	set_camera_ray(t_vec *ray_direction, t_camera *camera,
		mlx_window_create_info info)
{
	int		i;
	int		j;

	i = 0;
	while (i != info.height)
	{
		j = 0;
		while (j != info.width)
		{
			*ray_direction = calcule_ray_direction(camera, info, j, i);
			ray_direction++;
			j++;
		}
		i++;
	}
}
