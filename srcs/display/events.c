#include "miniRT.h"

void key_hook(int key, void* param)
{
	static bool	fullscreen = false;
	t_mlx 		*mlx;

	mlx = (t_mlx *)param;
    if(key == 41)
		mlx_loop_end(mlx->mlx);
	if (key == 68)
	{
		if (fullscreen == true)
			fullscreen = false;
		else
			fullscreen = true;
		mlx_set_window_fullscreen(mlx->mlx, mlx->win , fullscreen);
	}
//	printf("->%d\n", key);
}

void window_hook(int event, void* param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	if(event == 0)
		mlx_loop_end(mlx->mlx);
	if(event == 8)
	{
		mlx_get_window_size(mlx->mlx, mlx->win, &mlx->info.width, &mlx->info.height);
		printf("%d - %d\n", mlx->info.width, mlx->info.height);
	}
}
