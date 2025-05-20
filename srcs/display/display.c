
#include "miniRT.h"

// void	ft_display()
// {
// 	int	i;
// 	int	j;

// 	i = 
// 	mlx_pixel_put(mlx, mlx->win, i, j, (mlx_color){ .rgba = 0xFF0000FF});

// }

int	setup_display(t_data *data)
{
	t_mlx				*mlx;

	mlx = &data->mlx;
	mlx->mlx = mlx_init();
	mlx->info.title = "miniRT";
	mlx->info.width = 800;
	mlx->info.height = 800;
	mlx->info.is_resizable = true;
	mlx->info.is_fullscreen = false;

	mlx->win = mlx_new_window(mlx->mlx, &mlx->info);
	mlx->img = mlx_new_image(mlx->mlx, mlx->info.width, mlx->info.height);

	mlx_set_window_max_size(mlx->mlx, mlx->win, 1920, 1080);
	mlx_set_window_min_size(mlx->mlx, mlx->win, 400, 400);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, key_hook, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, window_hook, mlx);
    mlx_loop(mlx->mlx);

	// ft_display();

	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_context(mlx->mlx);
	return (0);
}
