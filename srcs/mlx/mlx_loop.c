#include "miniRT.h"

#include <time.h>

void	fps_cnt(void)
{
	static int frames = 0;
	static double lastTime = 0.0;
	static double fps = 0.0;

	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);  // temps système monotone
	double currentTime = ts.tv_sec + ts.tv_nsec / 1e9;

	frames++;

	if (currentTime - lastTime >= 1.0)
	{
		fps = frames / (currentTime - lastTime);
		printf("FPS: %.2f\n", fps);
		frames = 0;
		lastTime = currentTime;
	}
}

void	update_ray(t_data *data)
{
	data->setting_cam.rand_h = ((drand48() - 0.5) * data->setting_cam.res_h);
	data->setting_cam.rand_v = ((drand48() - 0.5) * data->setting_cam.res_v);
	(void)data;
}

void update(void* param)
{
	update_ray((t_data *)param);
	mouse((t_data *)param);
	display_screen((t_data *)param);
	(void)param;
	fps_cnt();
}

void	run_minirt(t_data *data)
{
	t_mlx	*mlx;

	mlx = &data->mlx;
	init_thread(data);
	mlx_add_loop_hook(mlx->mlx, update, data);
	mlx_loop(mlx->mlx);
	kill_thread(data->thread);
}
