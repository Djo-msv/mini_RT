/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:08:23 by star              #+#    #+#             */
/*   Updated: 2025/09/10 16:12:22 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void more_down(int key, void *param)
{
	if (key == 23)
	{
		((t_data *)param)->scene.camera.render_type = !((t_data *)param)->scene.camera.render_type;
		((t_data *)param)->image.nb_images = 0;
	}
	if (key == 8)
	{
		((t_data *)param)->scene.select.scale_mode = !((t_data *)param)->scene.select.scale_mode;
		((t_data *)param)->info.scale_mode = ((t_data *)param)->scene.select.scale_mode;
	}
	if (key == 21)
	{
		((t_data *)param)->scene.select.rotate_mode = !((t_data *)param)->scene.select.rotate_mode;
		((t_data *)param)->info.rotate_mode = ((t_data *)param)->scene.select.rotate_mode;
	}
	if (key == 224)
		((t_data *)param)->input.ctrl = true;
	if (key == 226)
		((t_data *)param)->input.alt = true;
	if (key == 24)
	{
		((t_data *)param)->scene.select.hit.type = -1;
		((t_data *)param)->info.obj = -1;
	}
}

static void	down(int key, void *param)
{
	if (key == 44)
		((t_data *)param)->input.space_button = true;
	if (key == 225)
		((t_data *)param)->input.shift_button = true;
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
	if (key == 38)
		((t_data *)param)->input.nine_button = true;
	if (key == 39)
		((t_data *)param)->input.zero_button = true;
	more_down(key, param);
}

void	key_hook_down(int key, void *param)
{
	static bool	fullscreen = false;
	t_mlx		*mlx;

	mlx = &((t_data *)param)->mlx;
	if (key == 41)
		mlx_loop_end(mlx->mlx);
	if (key == 43)
	{
		((t_data *)param)->scene.camera.aa = !((t_data *)param)->scene.camera.aa;
		((t_data *)param)->image.nb_images = 0;
		((t_data *)param)->info.aa = ((t_data *)param)->scene.camera.aa;
		print_info(&((t_data *)param)->info);
	}
	if (key == 26)
		((t_data *)param)->input.z_button = true;
	if (key == 22)
		((t_data *)param)->input.s_button = true;
	if (key == 7)
		((t_data *)param)->input.a_button = true;
	if (key == 4)
		((t_data *)param)->input.d_button = true;
	if (key == 68)
	{
		fullscreen = !fullscreen;
		mlx_set_window_fullscreen(mlx->mlx, mlx->win, fullscreen);
	}
	down(key, param);
}
