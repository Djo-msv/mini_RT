/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:06:52 by star              #+#    #+#             */
/*   Updated: 2025/09/25 19:33:09 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	more_key(int key, t_data *data)
{
	if (key == 43)
		change_antialiasing_mode(data);
	if (!(data->scene.select.hit.t <= 0))
		change_obj(data, data->scene.select.hit, key);
	if (key == 21)
		data->scene.select.rotate_mode = !data->scene.select.rotate_mode;
}

void	key_hook(int key, void *param)
{
	t_mlx		*mlx;

	mlx = &((t_data *)param)->mlx;
	if (key == 41)
		mlx_loop_end(mlx->mlx);
	if (key == 26 || key == 4 || key == 22 || key == 7)
		((t_data *)param)->image.nb_images = 0;
	if (key == 26)
		move_camera_forward((t_data *)param, &((t_data *)param)->setting_cam);
	if (key == 22)
		move_camera_backward((t_data *)param, &((t_data *)param)->setting_cam);
	if (key == 7)
		move_camera_left((t_data *)param, &((t_data *)param)->setting_cam);
	if (key == 4)
		move_camera_right((t_data *)param, &((t_data *)param)->setting_cam);
	if (key == 44)
		move_camera_up((t_data *)param, &((t_data *)param)->setting_cam);
	if (key == 225)
		move_camera_down((t_data *)param, &((t_data *)param)->setting_cam);
	more_key(key, ((t_data *)param));
}

void	window_hook(int event, void *param)
{
	t_mlx	*mlx;

	mlx = &((t_data *)param)->mlx;
	if (event == 0)
		mlx_loop_end(mlx->mlx);
}

void	mouse_hook(int button, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (button == 3)
	{
		data->setting_cam.move = !data->setting_cam.move;
		change_mode(data);
	}
	if (button == 1)
		handle_select_obj(data);
}

void	mouse_wheel_hook(int button, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (button == 2)
		data->image.resolution++;
	if (button == 1 && data->image.resolution > 1)
		data->image.resolution--;
	else if (data->image.resolution == 1)
		return ;
	if (button == 1 || button == 2)
	{
		data->image.nb_images = 0;
		calcule_res(data, &data->setting_cam);
	}
}
