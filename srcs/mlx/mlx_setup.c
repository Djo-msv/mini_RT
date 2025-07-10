#include "miniRT.h"

void	setup_mlx_window(t_mlx *mlx)
{
	mlx->info.title = "miniRT";
	mlx->info.width = 800;
	mlx->info.height = 800;
	mlx->info.is_resizable = true;
	mlx->info.is_fullscreen = false;
	mlx->win = mlx_new_window(mlx->mlx, &mlx->info);
	mlx->img = mlx_new_image(mlx->mlx, MAX_RES_W, MAX_RES_H);
	mlx_set_window_max_size(mlx->mlx, mlx->win, MAX_RES_W, MAX_RES_H);
	mlx_set_window_min_size(mlx->mlx, mlx->win, 400, 400);
//	mlx_set_fps_goal(mlx->mlx, 60);
}

void	setup_images(t_data *data)
{
	data->image.resolution = 1;
	data->image.antialiasing = 1;
	data->setting_cam.rbon_nb = 8;
	data->image.buf_img = ft_calloc(MAX_RES_H * MAX_RES_W, sizeof(t_fcolor));
//	data->image.old_img = ft_calloc(MAX_RES_H * MAX_RES_W, sizeof(t_fcolor));
	data->image.mlx_img = ft_calloc(MAX_RES_H * MAX_RES_W, sizeof(mlx_color));
}

void	setup_info(t_data *data, t_print_info *info)
{
	info->resolution = data->image.resolution;
	info->aa = data->image.antialiasing;
	info->x = data->mlx.info.width;
	info->y = data->mlx.info.height;
	info->first_display = true;
}

void	setup_events(t_data *data, t_mlx *mlx)
{
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, key_hook, data);
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, window_hook, data);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEDOWN, mouse_hook, data);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEWHEEL, mouse_wheel_hook, data);
}

int	setup_mlx(t_data *data)
{
	t_mlx	*mlx;
	t_print_info	*info;

	mlx = &data->mlx;
	info = &data->info;
	mlx->mlx = mlx_init();
	setup_mlx_window(mlx);
	setup_images(data);
	setup_info(data, info);
	setup_events(data, mlx);
	return (0);
}
