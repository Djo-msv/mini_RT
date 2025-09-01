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
	int	x;
	int	y;
//	float	pitch = 0;
//	float	yaw = 0;

//	t_camera *cam = &data->cam;
	mlx_mouse_get_pos(data->mlx.mlx, &x, &y);
	mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.info.width >> 1, data->mlx.info.height >> 1);
	if (x - (data->mlx.info.width >> 1) == 0 && y - (data->mlx.info.height >> 1) == 0)
		return ;
//	yaw += (x - (float)(data->mlx.info.width >> 1)) * 0.001f;
//	pitch += (y - (float)(data->mlx.info.height >> 1)) * 0.001f;

//	printf("\033[3A");
//	printf("forward : %f - %f - %f       \n", cam->forward.x, cam->forward.y, cam->forward.z);
//	printf("up      : %f - %f - %f       \n", cam->up.x, cam->up.y, cam->up.z);
//	printf("right   : %f - %f - %f       \n", cam->right.x, cam->right.y, cam->right.z);
//	rotate_camera(cam, 1.57f, 0.0f, 0.0f);
//	set_camera_ray(data->pool->ray_direction, cam, data->mlx.info);
}
// first yaw
// second yaw
// lasr roll
