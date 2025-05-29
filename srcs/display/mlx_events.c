#include "miniRT.h"

void key_hook(int key, void* param)
{
	static bool	fullscreen = false;
	t_mlx 		*mlx;

	mlx = &((t_data *)param)->mlx;
    if(key == 41)
		mlx_loop_end(mlx->mlx);
	if (key == 26 || key == 4 || key == 22 || key == 7)
		clear_image(mlx);
	if (key == 68)
	{
		fullscreen = !fullscreen;
		mlx_set_window_fullscreen(mlx->mlx, mlx->win , fullscreen);
	}
	if (key == 43)
		change_antialiasing_mode((t_data *)param);
//	printf("->%d\n", key);
}

void window_hook(int event, void* param)
{
	t_mlx *mlx;

	mlx = &((t_data *)param)->mlx;
	if(event == 0)
		mlx_loop_end(mlx->mlx);
	if (event == 8)
	{
		mlx_get_window_size(mlx->mlx, mlx->win, &mlx->info.width, &mlx->info.height);
		new_image((t_data *)param, mlx);
		ft_free_2d_tab((void **)((t_data *)param)->setting_cam.ray_direction);
		setup_camera_setting((t_data *)param);
	}
}

void mouse_hook(int button, void* param)
{
	t_data	*data = (t_data *)param;

    printf("-> %d\n", button);
	if (button == 3)
	{
		data->setting_cam.move = !data->setting_cam.move;
		change_mode(data);
	}
}

void mouse_wheel_hook(int button, void* param)
{
	t_data *data = (t_data *)param;

	if (button == 2)
		data->image.resolution++;
	if (button == 1 && data->image.resolution > 1)
		data->image.resolution--;
	else if (data->image.resolution == 1)
		return ;
	if (button == 1 || button == 2)
	{
		setup_camera_setting(data);
		data->image.nb_images = 0;
		printf("-> %d\n", data->image.resolution);
	}
	(void)param;
}
