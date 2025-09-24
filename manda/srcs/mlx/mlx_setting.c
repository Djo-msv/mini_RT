/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:35:53 by star              #+#    #+#             */
/*   Updated: 2025/09/24 18:40:31 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void	change_antialiasing_mode(t_data *data)
// {
// 	data->image.antialiasing = !data->image.antialiasing;
// 	data->image.nb_images = 0;
// }

void	change_mode(t_data *data)
{
	t_setting_cam	cam;

	cam = data->setting_cam;
	if (data->setting_cam.move)
	{
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, cam.width >> 1,
			cam.height >> 1);
		mlx_mouse_hide(data->mlx.mlx);
	}
	else
		mlx_mouse_show(data->mlx.mlx);
}
