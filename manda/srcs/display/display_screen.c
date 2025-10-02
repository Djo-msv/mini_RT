/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:30:46 by star              #+#    #+#             */
/*   Updated: 2025/10/01 19:21:14 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	handle_pixel(t_data *data, int x, int y, int resolution)
{
	int			pos;
	t_mlx		*mlx;

	mlx = &data->mlx;
	pos = y * mlx->info.width + x;
	render(data, &data->image.new_img[pos],
		data->setting_cam.ray_direction[x][y]);
	(void) resolution;
	if (resolution != 1)
		handle_low_resolution(data, x, y, resolution);
}

void	swap_img_buf(t_data *data)
{
	t_fcolor	*buf;

	buf = data->image.new_img;
	data->image.new_img = data->image.old_img;
	data->image.old_img = buf;
}

void	browse_pixel(int resolution, mlx_window_create_info info, t_data *d)
{
	int		x;
	int		y;

	y = 0;
	while (y < info.height)
	{
		x = 0;
		while (x < info.width)
		{
			handle_pixel(d, x, y, resolution);
			x += resolution;
		}
		y += resolution;
	}
}

void	display_screen(t_data *d)
{
	int						resolution;
	mlx_window_create_info	info;

	info = d->mlx.info;
	d->image.coef_new_p = ((float)d->image.nb_images
			/ (float)(d->image.nb_images + 1));
	d->image.coef_old_p = ((float)1.0 / (d->image.nb_images + 1));
	resolution = d->image.resolution;
	browse_pixel(resolution, info, d);
	fcolor_to_mlxcolor(d, d->image.new_img, d->image.mlx_img, info.width
		* info.height);
	mlx_set_image_region(d->mlx.mlx, d->mlx.img, 0, 0, info.width,
		info.height, d->image.mlx_img);
	mlx_clear_window(d->mlx.mlx, d->mlx.win, (mlx_color){.rgba = 0x000000FF});
	mlx_put_image_to_window(d->mlx.mlx, d->mlx.win, d->mlx.img, 0, 0);
	d->image.nb_images++;
}
