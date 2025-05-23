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

void	handle_pixel(t_data *data, int x, int y)
{
	int			pos;
	t_mlx		*mlx;

	mlx = &data->mlx;
//	if (x % data->param.resolution != 0 || y % data->param.resolution != 0)
//		return ;
	// calculer le pixel;
	pos = y * mlx->info.width + x;
	if (data->image.nb_images != 0)
		average_pixel(&data->image.new_img[pos], \
			data->image.old_img[pos], \
			data->image.coef_new_p, data->image.coef_old_p);
}

void	display_screen(t_data *data)
{
	int	x;
	int	y;
	int	resolution;
	mlx_color	*buf;
	mlx_window_create_info	info = data->mlx.info;


	y = 0;
	data->image.coef_old_p = (data->image.nb_images / (data->image.nb_images + 1));
	data->image.coef_new_p = (1 / (data->image.nb_images + 1));
//	resolution = data->param.resolution;
	resolution = 3;
	while (y < info.height)
	{
		x = 0;
		while (x < info.width)
		{
			handle_pixel(data, x, y);
			x += resolution;
		}
		y += resolution;
	}
	buf = 	data->image.new_img;
	data->image.new_img = data->image.old_img;
	data->image.old_img = buf;
//	printf("%zu\n", data->image.nb_images);
	data->image.nb_images++;
}
