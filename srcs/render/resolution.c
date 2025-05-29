#include "miniRT.h"

void	handle_low_resolution(t_data *data, int x, int y, int resolution)
{
	int	end_x;
	int	end_y;
	int	base_x = x;
	int	pos;
	mlx_color	*image;
	mlx_color	pixel;

	end_x = x + resolution;
	end_y = y + resolution;
//	printf("%d - %d / %d - %d\n", x, y, end_x, end_y);
	if (end_x > data->mlx.info.width)
		end_x = data->mlx.info.width;
	if (end_y > data->mlx.info.height)
		end_y = data->mlx.info.height;
	image = data->image.new_img;
	pixel = image[y * data->mlx.info.width + x];
	while (y != end_y)
	{
		pos = y * data->mlx.info.width;
		x = base_x;
		while (x != end_x)
		{
			image[pos + x] = pixel;
			x++;
		}
		y++;
	}
}
