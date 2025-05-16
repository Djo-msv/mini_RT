#include "miniRT.h"

void key_hook(int key, void* param)
{
	static bool	fullscreen = false;
	mlx_t 		*mlx;

	mlx = (mlx_t *)param;
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
	mlx_t *mlx;

	mlx = (mlx_t *)param;
	if(event == 0)
		mlx_loop_end(mlx->mlx);
}

