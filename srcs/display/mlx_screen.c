#include "miniRT.h"

void	handle_pixel(t_data *data, int x, int y, int resolution)
{
	int			pos;
	t_mlx		*mlx;

	mlx = &data->mlx;
	pos = y * mlx->info.width + x;
	render(data, &data->image.new_img[pos], data->setting_cam.ray_direction[x][y]);
//	if (data->image.nb_images >= 1)
//		average_pixel(&data->image.new_img[pos], \
//			data->image.old_img[pos], \
//			data->image.coef_new_p, data->image.coef_old_p);
	if (resolution != 1)
		handle_low_resolution(data, x, y, resolution);

}

void	swap_img_buf(t_data *data)
{
	t_fcolor	*buf;

	buf = 	data->image.new_img;
	data->image.new_img = data->image.old_img;
	data->image.old_img = buf;
}

void	display_screen(t_data *data)
{
	int	x;
	int	y;
	int	resolution;
	mlx_window_create_info	info = data->mlx.info;

	y = 0;
	data->image.coef_new_p = ((double)data->image.nb_images / (double)(data->image.nb_images + 1));
	data->image.coef_old_p = ((double)1.0 / (data->image.nb_images + 1));
//	printf("%lf - %lf\n", data->image.coef_new_p, data->image.coef_old_p);
	resolution = data->image.resolution;
	while (y < info.height)
	{
		x = 0;
		while (x < info.width)
		{
			handle_pixel(data, x, y, resolution);
			x += resolution;
		}
		y += resolution;
	}
	fcolor_to_mlxcolor(data, data->image.new_img, data->image.mlx_img, info.width * info.height);
	mlx_set_image_region(data->mlx.mlx, data->mlx.img, 0, 0, info.width, info.height, data->image.mlx_img);
	mlx_clear_window(data->mlx.mlx, data->mlx.win, (mlx_color){ .rgba = 0x000000FF});
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
//	swap_img_buf(data);
	data->image.nb_images++;
}
