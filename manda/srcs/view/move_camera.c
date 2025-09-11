/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:00:48 by star              #+#    #+#             */
/*   Updated: 2025/07/28 20:05:55 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_camera_forward(t_data *data, t_setting_cam *cam)
{
	t_vec	flat;

	flat = cam->forward;
	flat.y = 0;
	flat = normalize(flat);
	cam->camera_center.x += flat.x * 0.05f;
	cam->camera_center.z += flat.z * 0.05f;
	rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_backward(t_data *data, t_setting_cam *cam)
{
	t_vec	flat;

	flat = cam->forward;
	flat.y = 0;
	flat = normalize(flat);
	cam->camera_center.x -= flat.x * 0.05f;
	cam->camera_center.z -= flat.z * 0.05f;
	rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_left(t_data *data, t_setting_cam *cam)
{
	t_vec	up;
	t_vec	flat;
	t_vec	left;

	flat = cam->forward;
	up = (t_vec){0.0f, 1.0f, 0.0f};
	flat.y = 0;
	flat = normalize(flat);
	left = cross(up, flat);
	cam->camera_center.x += left.x * 0.05f;
	cam->camera_center.z += left.z * 0.05f;
	rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_right(t_data *data, t_setting_cam *cam)
{
	t_vec	up;
	t_vec	flat;
	t_vec	right;

	up = (t_vec){0.0f, 1.0f, 0.0f};
	flat = cam->forward;
	flat.y = 0;
	flat = normalize(flat);
	right = cross(up, flat);
	cam->camera_center.x -= right.x * 0.05f;
	cam->camera_center.z -= right.z * 0.05f;
	rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_up(t_data *data, t_setting_cam *cam)
{
	cam->camera_center.y += 0.05f;
	rotate_camera(data, cam->pitch, cam->yaw);
}
