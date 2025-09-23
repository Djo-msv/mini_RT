/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:38:36 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:28:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	setup_minirt(t_data *data)
{
	if (init_thread(data))
		return (1);
	if (setup_mlx(data))
	{
		tpool_destroy(data->pool);
		return (1);
	}
	set_camera_value(data, &data->cam);
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
		free_data(&data);
		return (1);
	}
	ft_add_texture(&data);
	run_minirt(&data);
	free_data(&data);
	return (0);
}
