/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:30:21 by star              #+#    #+#             */
/*   Updated: 2025/09/25 17:49:29 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	handle_low_resolution(t_data *data, int x, int y, int resolution)
{
	int			end_x;
	int			end_y;
	int			base_x;
	t_fcolor	*image;
	t_fcolor	pixel;

	base_x = x;
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
