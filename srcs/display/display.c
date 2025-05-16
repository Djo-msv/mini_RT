
#include "miniRT.h"

int	setup_display(void)
{
	mlx_t				mlx;
	mlx_window_create_info	info;

	mlx.mlx = mlx_init();
	info.title = "miniRT";
	info.width = 800;
	info.height = 800;
	info.is_resizable = true;
	info.is_fullscreen = false;

	mlx.win = mlx_new_window(mlx.mlx, &info);

	mlx_set_window_max_size(mlx.mlx, mlx.win, 1920, 1080);
	mlx_set_window_min_size(mlx.mlx, mlx.win, 400, 400);
	mlx_on_event(mlx.mlx, mlx.win, MLX_KEYDOWN, key_hook, &mlx);
//	mlx_on_event(mlx.mlx, mlx.win, MLX_WINDOW_EVENT, window_hook, &mlx);
    mlx_loop(mlx.mlx);

	mlx_destroy_window(mlx.mlx, mlx.win);
	mlx_destroy_context(mlx.mlx);
	return (0);
}
