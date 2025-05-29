#include "miniRT.h"

void	handle_pixel(t_data *data, int x, int y, int resolution)
{
	int			pos;
	t_mlx		*mlx;

	mlx = &data->mlx;
	pos = y * mlx->info.width + x;
	data->image.new_img[pos] = render(data, x, y);
	if (data->image.nb_images > 1)
		average_pixel(&data->image.new_img[pos], \
			data->image.old_img[pos], \
			data->image.coef_new_p, data->image.coef_old_p);
	if (resolution != 1)
		handle_low_resolution(data, x, y, resolution);

}

void	swap_img_buf(t_data *data)
{
	mlx_color	*buf;

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
	data->image.coef_new_p = ((float)data->image.nb_images / (float)(data->image.nb_images + 1));
	data->image.coef_old_p = (1.0f / (data->image.nb_images + 1));
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
	mlx_set_image_region(data->mlx.mlx, data->mlx.img, 0, 0, info.width, info.height, data->image.new_img);
	mlx_clear_window(data->mlx.mlx, data->mlx.win, (mlx_color){ .rgba = 0x000000FF});
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	swap_img_buf(data);
	data->image.nb_images++;
}
