#include "miniRT.h"

#include <time.h>

void	fps_cnt(void)
{
	static int frames = 0;
	static double lastTime = 0.0;
	static double fps = 0.0;

	clock_t currentClock = clock();
	double currentTime = (double)currentClock / CLOCKS_PER_SEC;

	frames++;

	if (currentTime - lastTime >= 1.0) // 1 seconde écoulée
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
	(void)param;
	update_ray((t_data *)param);
	mouse((t_data *)param);
	display_screen((t_data *)param);
	fps_cnt();
}

void	run_minirt(t_data *data)
{
	t_mlx	*mlx;

	mlx = &data->mlx;
	mlx_add_loop_hook(mlx->mlx, update, data);
	mlx_loop(mlx->mlx);
	free_data(data);
}
