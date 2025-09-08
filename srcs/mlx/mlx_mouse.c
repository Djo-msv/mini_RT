/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:36:30 by star              #+#    #+#             */
/*   Updated: 2025/07/31 19:36:38 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	mouse_update(t_data *data)
{
	int				x;
	int				y;
	t_camera	*cam;

	cam = &data->cam;
	mlx_mouse_get_pos(data->mlx.mlx, &x, &y);
	if (cam->move)
	{
		mlx_mouse_move(data->mlx.mlx, data->mlx.win,
			data->mlx.info.width >> 1, data->mlx.info.height >> 1);
		if (x - (data->mlx.info.width >> 1) == 0 && y - (data->mlx.info.height >> 1) == 0)
			return ;
		cam->yaw  -= (x - (float)(data->mlx.info.width >> 1)) * 0.001f;
		cam->pitch -= (y - (float)(data->mlx.info.height >> 1)) * 0.001f;
		if (cam->pitch > 1.5708f)
			cam->pitch = 1.5707f;
		if (cam->pitch < -1.5708f)
			cam->pitch = -1.5707f;
		rotate_camera(data, cam->pitch, cam->yaw);
	}
}
