/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:59:47 by star              #+#    #+#             */
/*   Updated: 2025/07/31 21:01:45 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <time.h>

void	fps_cnt(t_data *data)
{
	static int		frames = 0;
	static double	lasttime = 0.0;
	static double	fps = 0.0;
	double			currenttime;
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);// temps système monotone
	currenttime = ts.tv_sec + ts.tv_nsec / 1e9;
	frames++;
	if (currenttime - lasttime >= 1.0)
	{
		fps = frames / (currenttime - lasttime);
		data->info.fps = fps;
		print_info(&data->info);
		frames = 0;
		lasttime = currenttime;
	}
}

void	update_antialiasing(t_data *data)
{
	data->scene.camera.rand_h = ((drand48() - 0.5)
			* (data->cam.d_width / data->mlx.info.width));
	data->scene.camera.rand_v = ((drand48() - 0.5)
			* (data->cam.d_height / data->mlx.info.height));
	(void)data;
}

void	update(void *param)
{
	update_antialiasing((t_data *)param);
	swap_buffer(((t_data *)param)->pool);
	update_input((t_data *)param);
	lunch_thread((t_data *)param);
//	if buffer ready	
	display_screen((t_data *)param);
	fps_cnt((t_data *)param);
}

void	run_minirt(t_data *data)
{
	t_mlx	*mlx;

	mlx = &data->mlx;
	mlx_add_loop_hook(mlx->mlx, update, data);
	mlx_loop(mlx->mlx);
	tpool_destroy(data->pool);
}
