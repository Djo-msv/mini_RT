#include "miniRT.h"

void	clear_image(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	while (x != mlx->info.height)
	{
		y = 0;
		while (y != mlx->info.width)
			mlx_set_image_pixel(mlx->mlx, mlx->img, y++, x, (mlx_color){ .rgba = 0x000000FF });
		x++;
	}
}

void	new_image(t_data *data, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	free(data->image.new_img);
	free(data->image.old_img);
	data->image.nb_images = 0;
	mlx->img = mlx_new_image(mlx->mlx, mlx->info.width, mlx->info.height);
	data->image.new_img = ft_calloc(mlx->info.width * mlx->info.height,sizeof(mlx_color));
	data->image.old_img = ft_calloc(mlx->info.width * mlx->info.height,sizeof(mlx_color));
}
