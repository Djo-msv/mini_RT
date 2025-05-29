#include "miniRT.h"

void	change_antialiasing_mode(t_data *data)
{
	data->image.antialiasing = !data->image.antialiasing;
	clear_image(&data->mlx);
	data->image.nb_images = 0;
}


void	change_mode(t_data *data)
{
	if (data->setting_cam.move)
		mlx_mouse_hide(data->mlx.mlx);
	else
		mlx_mouse_show(data->mlx.mlx);
}

