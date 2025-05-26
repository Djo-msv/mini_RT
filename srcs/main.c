/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:44:44 by nrolland          #+#    #+#             */
/*   Updated: 2025/05/16 17:38:46 by nrolland         ###   ########.fr       */
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
//	if (parse(&ata, argc, agrv))
//		return (1);
	setup_minirt(&data);
	run_minirt(&data);
	return(0);
}
