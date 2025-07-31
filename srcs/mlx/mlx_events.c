/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:06:52 by star              #+#    #+#             */
/*   Updated: 2025/07/31 18:53:08 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	down(int key, void *param)
{
	if (key == 42)
		((t_data *)param)->input.deletion_button = true;
	if (key == 82)
		((t_data *)param)->input.up_button = true;
	if (key == 81)
		((t_data *)param)->input.down_button = true;
	if (key == 80)
		((t_data *)param)->input.left_button = true;
	if (key == 79)
		((t_data *)param)->input.right_button = true;
	if (key == 45)
		((t_data *)param)->input.minus_button = true;
	if (key == 46)
		((t_data *)param)->input.plus_button = true;
}

void key_hook_down(int key, void *param)
{
	static bool	fullscreen = false;
	t_mlx 					*mlx;

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
	down(key, param);
}

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
}

void key_hook_up(int key, void *param)
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
		((t_data *)param)->pool->restart = 1;
	}
}

// void	handle_select_obj(t_data *d)
// {
// 	t_ray	ray;
// 	int		x;
// 	int		y;

// 	x = 0;
// 	y = 0;
// 	if (d->setting_cam.move)
// 		ray = create_ray(d->setting_cam.camera_center, d->setting_cam.forward);
// 	else
// 	{
// 		mlx_mouse_get_pos(d->mlx.mlx, &x, &y);
// 		t_vec	pixel_center;
// 		pixel_center = vec_add(
// 			vec_add(d->setting_cam.pixel00_loc, vec_mul(d->setting_cam.pixel_delta_h, x)),
// 			vec_mul(d->setting_cam.pixel_delta_v, y));
// 		ray = create_ray(d->setting_cam.camera_center, vec_sub(pixel_center, d->setting_cam.camera_center));
// 	}
// 	d->scene.select.hit = nearest_obj(d, ray, true);
// 	if (d->scene.select.hit.t <= 0)
// 		return ;
// 	if (d->setting_cam.move)
// 		destroy_obj(d, d->scene.select.hit);
// }

// void mouse_hook(int button, void* param)
// {
// 	t_data	*data = (t_data *)param;

// 	// if (button == 3)
// 	// {
// 	// 	data->setting_cam.move = !data->setting_cam.move;
// 	// 	change_mode(data);
// 	// }
// 	if (button == 1)
// 		handle_select_obj(data);
// }
/*

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
