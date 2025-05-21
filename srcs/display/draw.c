#include "miniRT.h"

int	draw_background(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, mlx->info.width, mlx->info.height);
	while (x != mlx->info.width)
	{
		y = 0;
		while (y != mlx->info.height)
		{
			if (((150 - x )* (150 - x) ) + ((150 - y) * (150 - y)) < 350.)
				mlx_set_image_pixel(mlx->mlx, mlx->img, x, y, (mlx_color){ .rgba = 0xFF0000FF });
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}
