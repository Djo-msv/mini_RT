/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:56:39 by star              #+#    #+#             */
/*   Updated: 2025/07/30 16:29:38 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	angle_camera(t_data *data, float pitch, float yaw)
{
	t_vec	forward;
	t_vec	right;
	t_vec	up;

	forward = (t_vec){
		cos(pitch) * sin(yaw),
		sin(pitch),
		cos(pitch) * cos(yaw)
	};
	data->setting_cam.forward = normalize(forward);
	right = normalize(cross(data->setting_cam.forward,
				(t_vec){0.0f, 1.0f, 0.0f}));
	up = cross(right, data->setting_cam.forward);
	data->setting_cam.viewport_h = vec_scale(right,
			data->setting_cam.viewport_width);
	data->setting_cam.viewport_v = vec_scale(up,
			data->setting_cam.viewport_height);
}

void	rotate_camera(t_data *data, float pitch, float yaw)
{
	angle_camera(data, pitch, yaw);
	calcule_res(data, &data->setting_cam);
	calculate_ray_direction(&data->setting_cam);
	data->image.nb_images = 0;
}

void	move_camera_down(t_data *data, t_setting_cam *cam)
{
	cam->camera_center.y -= 0.05f;
	rotate_camera(data, cam->pitch, cam->yaw);
}
