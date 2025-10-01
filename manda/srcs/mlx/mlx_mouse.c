/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:33:52 by star              #+#    #+#             */
/*   Updated: 2025/10/01 19:21:14 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	mouse(t_data *data)
{
	int				x;
	int				y;
	t_setting_cam	*cam;

	cam = &data->setting_cam;
	mlx_mouse_get_pos(data->mlx.mlx, &x, &y);
	if (data->setting_cam.move)
	{
		mlx_mouse_move(data->mlx.mlx, data->mlx.win,
			cam->width >> 1, cam->height >> 1);
		if (x - (cam->width >> 1) == 0 && y - (cam->height >> 1) == 0)
			return ;
		cam->yaw += (x - (float)(cam->width >> 1)) * 0.001f;
		cam->pitch -= (y - (float)(cam->height >> 1)) * 0.001f;
		if (cam->pitch > 1.5708f)
			cam->pitch = 1.5707f;
		if (cam->pitch < -1.5708f)
			cam->pitch = -1.5707f;
		rotate_camera(data, cam->pitch, cam->yaw);
	}
}
