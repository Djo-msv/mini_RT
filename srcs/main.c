#include "miniRT.h"

void		setup_minirt(t_data *data)
{
	setup_mlx(data);
	setup_camera_setting(data);
}

int	ft_get_width(mlx_image img, t_data *data)
{
	mlx_color	color;
	int			x;

	x = 0;
	while (1)
	{
		color = mlx_get_image_pixel(data->mlx.mlx, img, x, 0);
		if (color.rgba == 0x00000000)
			break ;
		x++;
	}
	return (x);
}

int	ft_get_height(mlx_image img, t_data *data)
{
	mlx_color color;
	int y;

	y = 0;
	while (1)
	{
		color = mlx_get_image_pixel(data->mlx.mlx, img, y, 0);
		if (color.rgba == 0x00000000)
			break ;
		y++;
	}
	return (y);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(data));
	if (parse(&data, argc, argv))
		return (1);
	setup_minirt(&data);
	data.tex.image = mlx_new_image_from_file(data.mlx.mlx, "texture/bumb.jpg", 0, 0);
	data.tex.width = ft_get_width(data.tex.image, &data);
	data.tex.height = ft_get_height(data.tex.image, &data);
	run_minirt(&data);
	free_data(&data);
	return(0);
}
