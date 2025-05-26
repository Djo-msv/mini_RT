#include "miniRT.h"

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
