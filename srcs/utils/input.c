/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:38:18 by star              #+#    #+#             */
/*   Updated: 2025/07/31 20:54:14 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_camera(t_data *data, t_input input)
{
	if (input.z_button)
		move_camera_forward(data, &data->cam);
	if (input.s_button)
		move_camera_backward(data, &data->cam);
	if (input.a_button)
		move_camera_left(data, &data->cam);
	if (input.d_button)
		move_camera_right(data, &data->cam);
	if (input.space_button)
		move_camera_up(data, &data->cam);
	if (input.shift_button)
		move_camera_down(data, &data->cam);
}

void	update_input(t_data *data)
{
	int		tmp;
	t_input	i;

	i = data->input;
	tmp = data->info.nb_input;
	data->info.nb_input = i.z_button + i.s_button + i.a_button + i.d_button
		+ i.space_button + i.shift_button + i.deletion_button + i.down_button
		+ i.left_button + i.up_button + i.right_button + i.minus_button
		+ i.plus_button + i.nine_button + i.zero_button;
	if (data->info.nb_input != tmp)
		print_info(&data->info);
	if (data->pool->restart)
	{
		data->pool->restart = 0;
		data->image.nb_images = 0;
		set_param(data);
		set_camera_window(data, &(data->cam));
		set_camera_ray(data->pool->ray_direction, &(data->cam), data->mlx.info);
	}
	if (i.move)
	{
		if (data->info.nb_input)
			move_camera(data, i);
		mouse_update(data);
	}
//	rotate_camera(0.0f, 0.0f, 0.0f, &(data->cam.forward);
//	printf("%f - %f - %f\n", vec->x, vec->y, vec->z);
}
