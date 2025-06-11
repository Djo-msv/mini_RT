#include "miniRT.h"

void	handle_low_resolution(t_data *data, int x, int y, int resolution)
{
	int	end_x;
	int	end_y;
	int	base_x = x;
	t_fcolor	*image;
	t_fcolor	pixel;

	end_x = x + resolution;
	end_y = y + resolution;
	if (end_x > data->mlx.info.width)
		end_x = data->mlx.info.width;
	if (end_y > data->mlx.info.height)
		end_y = data->mlx.info.height;
	pixel = data->image.new_img[y * data->mlx.info.width + x];
	while (y != end_y)
	{
		x = base_x;
		image = &data->image.new_img[y * data->mlx.info.width + x];
		while (x != end_x)
		{
			*image++ = pixel;
			x++;
		}
		y++;
	}
}
