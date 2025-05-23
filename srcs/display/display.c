
#include "miniRT.h"

void update(void* param)
{
	display_screen((t_data *)param);
}

void	setup_param(t_data *data)
{
	data->param.resolution = 1;
	data->param.rbon_nb = 1;
	data->image.new_img = ft_calloc(800 * 800, sizeof(mlx_color));
	data->image.old_img = ft_calloc(800 * 800, sizeof(mlx_color));
}

void	setup_info(t_mlx *mlx)
{
	mlx->info.title = "miniRT";
	mlx->info.width = 800;
	mlx->info.height = 800;
	mlx->info.is_resizable = true;
	mlx->info.is_fullscreen = false;
	mlx->win = mlx_new_window(mlx->mlx, &mlx->info);
	mlx->img = mlx_new_image(mlx->mlx, mlx->info.width, mlx->info.height);
	mlx_set_window_max_size(mlx->mlx, mlx->win, 1920, 1080);
	mlx_set_window_min_size(mlx->mlx, mlx->win, 400, 400);
//	mlx_set_fps_goal(mlx->mlx, 60);
}

int	setup_display(t_data *data)
{
	t_mlx				*mlx;

	mlx = &data->mlx;
	mlx->mlx = mlx_init();
	setup_param(data);
	setup_info(mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, key_hook, data);
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, window_hook, data);
	mlx_add_loop_hook(mlx->mlx, update, data);
    mlx_loop(mlx->mlx);

	// ft_display();

	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_context(mlx->mlx);
	free(data->image.new_img);
	free(data->image.old_img);
	return (0);
}
