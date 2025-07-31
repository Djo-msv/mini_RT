/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:38:36 by star              #+#    #+#             */
/*   Updated: 2025/07/31 21:02:21 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	setup_minirt(t_data *data)
{
	init_thread(data);
	setup_mlx(data);
	set_camera_value(data, &data->cam);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(data));
	if (parse(&data, argc, argv))
		return (1);
	setup_minirt(&data);
	ft_add_texture(&data);
	run_minirt(&data);
	free_data(&data);
	return (0);
}
