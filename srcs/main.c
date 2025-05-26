/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:44:44 by nrolland          #+#    #+#             */
/*   Updated: 2025/05/26 19:18:01 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	setup_minirt(t_data *data)
{
	setup_mlx(data);
	setup_camera_setting(data);
}

int	main(int argc, char **argv)
{
	t_data data;

	(void) argc;
	(void) argv;
	ft_memset(&data, 0, sizeof(data));
	if (parse(&data, argc, argv))
		return (1);
	setup_minirt(&data);
	run_minirt(&data);
	return(0);
}
