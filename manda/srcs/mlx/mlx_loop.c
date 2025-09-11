/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:41:41 by star              #+#    #+#             */
/*   Updated: 2025/07/28 15:41:16 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	update_ray(t_data *data)
{
	data->setting_cam.rand_h = ((drand48() - 0.5) * data->setting_cam.res_h);
	data->setting_cam.rand_v = ((drand48() - 0.5) * data->setting_cam.res_v);
	(void)data;
}

void	update(void *param)
{
	update_ray((t_data *)param);
	mouse((t_data *)param);
	display_screen((t_data *)param);
}

void	run_minirt(t_data *data)
{
	t_mlx	*mlx;

	mlx = &data->mlx;
	mlx_add_loop_hook(mlx->mlx, update, data);
	mlx_loop(mlx->mlx);
}
