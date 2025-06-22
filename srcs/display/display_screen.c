#include "miniRT.h"





void	display_screen(t_data *data)
{
	mlx_window_create_info	info = data->mlx.info;

//	data->image.coef_new_p = ((double)data->image.nb_images / (double)(data->image.nb_images + 1));
//	data->image.coef_old_p = ((double)1.0 / (data->image.nb_images + 1));

	fcolor_to_mlxcolor(data, data->image.mlx_img);
	mlx_set_image_region(data->mlx.mlx, data->mlx.img, 0, 0, info.width, info.height, data->image.mlx_img);
	mlx_clear_window(data->mlx.mlx, data->mlx.win, (mlx_color){ .rgba = 0x000000FF});
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
//	data->image.nb_images++;
}
