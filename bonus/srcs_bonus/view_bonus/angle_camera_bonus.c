/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_camera_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:54:06 by star              #+#    #+#             */
/*   Updated: 2025/09/17 19:01:52 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	angle_camera(t_data *data, float pitch, float yaw)
{
	t_vec	forward;

	forward = (t_vec){
		cos(pitch) * sin(yaw),
		sin(pitch),
		cos(pitch) * cos(yaw)
	};
	data->cam.forward = normalize(forward);
	data->cam.right = normalize(cross(data->cam.forward,
				(t_vec){0.0f, 1.0f, 0.0f}));
	data->cam.up = cross(data->cam.right, data->cam.forward);
}

void	rotate_camera(t_data *data, float pitch, float yaw)
{
	angle_camera(data, pitch, yaw);
	set_camera_ray(data->pool->ray_direction, &data->cam, data->mlx.info);
	data->image.nb_images = 0;
}

void	move_camera_up(t_data *data, t_camera *cam)
{
	cam->coordinate.y += 0.05f;
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;
}

void	move_camera_down(t_data *data, t_camera *cam)
{
	cam->coordinate.y -= 0.05f;
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;
}
