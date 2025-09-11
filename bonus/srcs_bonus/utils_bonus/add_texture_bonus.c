/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_texture_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:45:58 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:28:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static int	ft_get_width(mlx_image img, t_data *data)
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

static int	ft_get_height(mlx_image img, t_data *data)
{
	mlx_color	color;
	int			y;

	y = 0;
	while (1)
	{
		color = mlx_get_image_pixel(data->mlx.mlx, img, 0, y);
		if (color.rgba == 0x00000000)
			break ;
		y++;
	}
	return (y);
}

void	ft_add_texture(t_data *d)
{
	t_list		*tmp;
	t_sphere	*sphere;

	tmp = d->scene.sphere;
	while (tmp)
	{
		sphere = (t_sphere *)tmp->content;
		if (sphere->tex.is_texture)
		{
			sphere->tex.image = mlx_new_image_from_file(d->mlx.mlx,
					sphere->tex.name, 0, 0);
			sphere->tex.width = ft_get_width(sphere->tex.image, d);
			sphere->tex.height = ft_get_height(sphere->tex.image, d);
		}
		if (sphere->tex.is_normal && sphere->tex.is_texture)
		{
			sphere->tex.n_image = mlx_new_image_from_file(d->mlx.mlx,
					sphere->tex.n_name, 0, 0);
			if (sphere->tex.width != ft_get_width(sphere->tex.n_image, d)
				|| sphere->tex.height != ft_get_height(sphere->tex.n_image, d))
				sphere->tex.is_normal = 0;
		}
		tmp = tmp->next;
	}
}
