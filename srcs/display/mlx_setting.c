#include "miniRT.h"

void	change_antialiasing_mode(t_data *data)
{
	data->image.antialiasing = !data->image.antialiasing;
	clear_image(&data->mlx);
	data->image.nb_images = 0;
}


void	change_mode(t_data *data)
{
	t_setting_cam cam = data->setting_cam;

	if (data->setting_cam.move)
	{
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, cam.width >> 1, cam.height >> 1);
		mlx_mouse_hide(data->mlx.mlx);
	}
	else
		mlx_mouse_show(data->mlx.mlx);
}
