/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:06:52 by star              #+#    #+#             */
/*   Updated: 2025/09/24 18:54:29 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	up(int key, void *param)
{
	if (key == 82)
		((t_data *)param)->input.up_button = false;
	if (key == 81)
		((t_data *)param)->input.down_button = false;
	if (key == 80)
		((t_data *)param)->input.left_button = false;
	if (key == 79)
		((t_data *)param)->input.right_button = false;
	if (key == 45)
		((t_data *)param)->input.minus_button = false;
	if (key == 46)
		((t_data *)param)->input.plus_button = false;
	if (key == 38)
		((t_data *)param)->input.nine_button = false;
	if (key == 39)
		((t_data *)param)->input.zero_button = false;
	if (key == 224)
		((t_data *)param)->input.ctrl = false;
	if (key == 226)
		((t_data *)param)->input.alt = false;
}

void	key_hook_up(int key, void *param)
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
	if (key == 42)
		((t_data *)param)->input.deletion_button = false;
	up(key, param);
}

void	window_hook(int event, void *param)
{
	t_mlx	*mlx;

	mlx = &((t_data *)param)->mlx;
	if (event == 0)
		mlx_loop_end(mlx->mlx);
	if (event == 8)
	{
		mlx_get_window_size(mlx->mlx, mlx->win,
			&mlx->info.width, &mlx->info.height);
		((t_data *)param)->info.y = mlx->info.width;
		((t_data *)param)->info.x = mlx->info.height;
		print_info(&((t_data *)param)->info);
		if (mlx->info.width > MAX_RES_W || mlx->info.height > MAX_RES_H)
		{
			mlx->info.width = MAX_RES_W;
			mlx->info.height = MAX_RES_H;
			mlx_set_window_fullscreen(mlx->mlx, mlx->win, false);
			return ;
		}
		((t_data *)param)->pool->restart = 1;
	}
}

void	handle_select_obj(t_data *d)
{
	t_ray	ray;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (d->input.move)
		ray = create_ray(d->cam.coordinate, d->cam.forward);
	else
	{
		mlx_mouse_get_pos(d->mlx.mlx, &x, &y);
		ray = create_ray(d->cam.coordinate,
				calcule_ray_direction(&d->cam, d->mlx.info, x, y));
	}
	d->scene.select.hit = nearest_obj(d->scene, ray, true);
	if (d->scene.select.hit.t <= 0)
	{
		d->info.obj = -1;
		return ;
	}
	else
		d->info.obj = d->scene.select.hit.type;
}

void	mouse_hook(int button, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (button == 3)
	{
		data->input.move = !data->input.move;
		if (!data->input.move)
			mlx_mouse_show(data->mlx.mlx);
		else
			mlx_mouse_hide(data->mlx.mlx);
		mlx_mouse_move(data->mlx.mlx, data->mlx.win,
			data->mlx.info.width >> 1, data->mlx.info.height >> 1);
	}
	if (button == 1)
		handle_select_obj(data);
}

// void	mouse_wheel_hook(int button, void *param)
// {
// 	t_data	*data;

// 	data = (t_data *)param;
// 	if (button == 2)
// 		data->image.resolution++;
// 	if (button == 1 && data->image.resolution > 1)
// 		data->image.resolution--;
// 	else if (data->image.resolution == 1)
// 		return ;
// 	if (button == 1 || button == 2)
// 	{
// 		data->image.nb_images = 0;
// 		calcule_res(data, &data->setting_cam);
// 	}
// }
