#include "miniRT.h"

void	average_pixel(mlx_color *n_pixel, mlx_color o_pixel, float coef_new_p, float coef_old_p)
{
	float	tmp;

	tmp = n_pixel->r * coef_old_p + o_pixel.r * coef_new_p;
	n_pixel->r = (uint8_t)(tmp + 0.5f); 
	tmp = n_pixel->g * coef_old_p + o_pixel.g * coef_new_p;
	n_pixel->g = (uint8_t)(tmp + 0.5f); 
	tmp = n_pixel->b * coef_old_p + o_pixel.b * coef_new_p;
	n_pixel->b = (uint8_t)(tmp + 0.5f); 
}

void	handle_low_resolution(t_data *data, int x, int y, int resolution)
{
	int	end_x;
	int	end_y;
	int	pos;
	mlx_color	*image;
	mlx_color	pixel;

	end_x = x + resolution;
	end_y = y + resolution;
	if (end_x > data->mlx.info.width)
		end_x = data->mlx.info.width;
	if (end_y > data->mlx.info.height)
		end_y = data->mlx.info.height;
	image = data->image.new_img;
	pixel = image[y * data->mlx.info.width + x];
	x += resolution + 1;
	while (y != end_y)
	{
		pos = y * data->mlx.info.width;
		x -= resolution;
		while (x != end_x)
		{
			image[pos + x] = pixel;
			x++;
		}
		y++;
	}
}

void	handle_pixel(t_data *data, int x, int y, int resolution)
{
	int			pos;
	t_mlx		*mlx;

	mlx = &data->mlx;
	pos = y * mlx->info.width + x;
	data->image.new_img[pos] = render(data, x, y);
	if (data->image.nb_images != 0)
		average_pixel(&data->image.new_img[pos], \
			data->image.old_img[pos], \
			data->image.coef_new_p, data->image.coef_old_p);
	if (resolution != 1)
		handle_low_resolution(data, x, y, resolution);
}

void	display_screen(t_data *data)
{
	int	x;
	int	y;
	int	resolution;
	mlx_color	*buf;
	mlx_window_create_info	info = data->mlx.info;


	y = 0;
	data->image.coef_old_p = ((float)data->image.nb_images / (float)(data->image.nb_images + 1));
	data->image.coef_new_p = (1.0f / (data->image.nb_images + 1));
//	resolution = data->param.resolution;
	resolution = 8;
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
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	buf = 	data->image.new_img;
	data->image.new_img = data->image.old_img;
	data->image.old_img = buf;
	data->image.nb_images++;
}
