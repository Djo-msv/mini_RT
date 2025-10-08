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

static float	frand(void)
{
	struct timeval	tv;
	unsigned long	seed ;

	gettimeofday(&tv, NULL);
	seed = (tv.tv_sec ^ tv.tv_usec);
	seed = (1103515245 * seed + 12345) & 0x7fffffff;
	return ((float)seed / 2147483647.0f);
}

float	ft_frand48(float min, float max)
{
	return (min + frand() * (max - min));
}

void	update_ray(t_data *data)
{
	if (!data->scene.camera.is_cam)
		return ;
	data->setting_cam.rand_h = (ft_frand48(-0.5, 0.5)
			* data->setting_cam.res_h);
	data->setting_cam.rand_v = (ft_frand48(-0.5, 0.5)
			* data->setting_cam.res_v);
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
