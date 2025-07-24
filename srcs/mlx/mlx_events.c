/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:06:52 by star              #+#    #+#             */
/*   Updated: 2025/07/15 17:43:06 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void key_hook_down(int key, void* param)
{
	static bool	fullscreen = false;
	t_mlx 		*mlx;

	mlx = &((t_data *)param)->mlx;
    if(key == 41)
		mlx_loop_end(mlx->mlx);
	if (key == 26)
		((t_data *)param)->input.z_button = true;
	if (key == 22)
		((t_data *)param)->input.s_button = true;
	if (key == 7)
		((t_data *)param)->input.a_button = true;
	if (key == 4)
		((t_data *)param)->input.d_button = true;
	if (key == 44)
		((t_data *)param)->input.space_button = true;
	if (key == 225)
		((t_data *)param)->input.shift_button = true;
	if (key == 68)
	{
		fullscreen = !fullscreen;
		mlx_set_window_fullscreen(mlx->mlx, mlx->win , fullscreen);
	}
}

void key_hook_up(int key, void* param)
{
	if (key == 26)
		((t_data *)param)->input.z_button = false;
	if (key == 22)
		((t_data *)param)->input.s_button = false;
	if (key == 7)
		((t_data *)param)->input.a_button = false;
	if (key == 4)
		((t_data *)param)->input.d_button = false;
	if (key == 44)
		((t_data *)param)->input.space_button = false;
	if (key == 225)
		((t_data *)param)->input.shift_button = false;
}

void window_hook(int event, void* param)
{
	t_mlx *mlx;

	mlx = &((t_data *)param)->mlx;
	if(event == 0)
		mlx_loop_end(mlx->mlx);
	if (event == 8)
	{
		mlx_get_window_size(mlx->mlx, mlx->win, &mlx->info.width, &mlx->info.height);
		((t_data *)param)->info.y = mlx->info.width;
		((t_data *)param)->info.x = mlx->info.height;
		print_info(&((t_data *)param)->info);
	}
}

/*

void mouse_hook(int button, void* param)
{
	t_data	*data = (t_data *)param;

	if (button == 3)
	{
		data->setting_cam.move = !data->setting_cam.move;
		change_mode(data);
	}
	if (button == 1)
		handle_select_obj(data);
}

void mouse_wheel_hook(int button, void* param)
{
	t_data *data = (t_data *)param;

	if (button == 2)
		data->image.resolution++;
	if (button == 1 && data->image.resolution > 1)
		data->image.resolution--;
	else if (data->image.resolution == 1)
		return ;
	if (button == 1 || button == 2)
	{
		data->image.nb_images = 0;
//		calcule_res(data, &data->setting_cam);
	}
}
*/
