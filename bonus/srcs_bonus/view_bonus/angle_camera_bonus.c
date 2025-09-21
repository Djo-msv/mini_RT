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
//	data->cam.viewport_h = vec_scale(right,
//			data->cam.viewport_width);
//	data->cam.viewport_v = vec_scale(up,
//			data->setting_cam.viewport_height);
}
/*
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
}*/

void	rotate_camera(t_data *data, float pitch, float yaw)
{
	angle_camera(data, pitch, yaw);
//	calcule_res(data, &data->cam);
	set_camera_ray(data->pool->ray_direction, &data->cam, data->mlx.info);
	(void)yaw;
	(void)pitch;

	data->image.nb_images = 0;
}

void	move_camera_up(t_data *data, t_camera *cam)
{
	cam->coordinate.y += 0.05f;
//	rotate_camera(data, cam->pitch, cam->yaw);
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;
}

void	move_camera_down(t_data *data, t_camera *cam)
{
	cam->coordinate.y -= 0.05f;
//	rotate_camera(data, cam->pitch, cam->yaw);
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;
}
