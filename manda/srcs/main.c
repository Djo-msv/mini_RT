/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:05:34 by star              #+#    #+#             */
/*   Updated: 2025/09/22 17:50:00 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	setup_minirt(t_data *data)
{
	if (setup_mlx(data))
		return (1);
	if (setup_camera_setting(data))
	{
		free(data->image.new_img);
		free(data->image.old_img);
		free(data->image.mlx_img);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(data));
	if (parse(&data, argc, argv))
		return (1);
	if (setup_minirt(&data))
	{
		ft_lstclear(&data.scene.light, free);
		ft_lstclear(&data.scene.cylinder, free);
		ft_lstclear(&data.scene.plane, free);
		ft_lstclear(&data.scene.sphere, free);
		return (1);
	}
	run_minirt(&data);
	free_data(&data);
	return (0);
}
