/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:02:27 by star              #+#    #+#             */
/*   Updated: 2025/09/24 18:36:55 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	handle_select_obj(t_data *d)
{
	t_ray	ray;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (d->setting_cam.move)
		ray = create_ray(d->setting_cam.camera_center, d->setting_cam.forward);
	else
	{
		mlx_mouse_get_pos(d->mlx.mlx, &x, &y);
		ray = create_ray(d->setting_cam.camera_center,
				d->setting_cam.ray_direction[x][y]);
	}
	d->scene.select.hit = nearest_obj(d, ray, true);
	if (d->scene.select.hit.t <= 0)
		return ;
}
