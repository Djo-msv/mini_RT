/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:58:01 by star              #+#    #+#             */
/*   Updated: 2025/10/01 19:42:21 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	move_camera_forward(t_data *data, t_camera *cam)
{
	t_vec	flat;

	flat = cam->forward;
	if (fabsf(cam->forward.y) > 0.999f)
		flat = cam->up;
	flat.y = 0;
	flat = normalize(flat);
	cam->coordinate.x += flat.x * 0.05f;
	cam->coordinate.z += flat.z * 0.05f;
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;
}

void	move_camera_backward(t_data *data, t_camera *cam)
{
	t_vec	flat;

	flat = cam->forward;
	if (fabsf(cam->forward.y) > 0.999f)
		flat = cam->up;
	flat.y = 0;
	flat = normalize(flat);
	cam->coordinate.x -= flat.x * 0.05f;
	cam->coordinate.z -= flat.z * 0.05f;
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;
}

void	move_camera_left(t_data *data, t_camera *cam)
{
	t_vec	up;
	t_vec	flat;
	t_vec	left;

	up = (t_vec){0.0f, 1.0f, 0.0f};
	flat = cam->forward;
	if (fabsf(cam->forward.y) >= 1.0f)
		flat = cam->up;
	flat.y = 0;
	flat = normalize(flat);
	left = cross(up, flat);
	cam->coordinate.x -= left.x * 0.05f;
	cam->coordinate.z -= left.z * 0.05f;
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;
}

void	move_camera_right(t_data *data, t_camera *cam)
{
	t_vec	up;
	t_vec	flat;
	t_vec	right;

	up = (t_vec){0.0f, 1.0f, 0.0f};
	flat = cam->forward;
	if (fabsf(cam->forward.y) > 0.999f)
		flat = cam->up;
	flat.y = 0;
	flat = normalize(flat);
	right = cross(up, flat);
	cam->coordinate.x += right.x * 0.05f;
	cam->coordinate.z += right.z * 0.05f;
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;
}
