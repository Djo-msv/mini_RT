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

int	main(int argc, char **agrv)
{
	t_data d;

	ft_memset(&d, 0, sizeof(d));
	if (parse(&d, argc, agrv))
		return (1);
	print_scene(d.scene);
	setup_display(&d);
	return(0);
}
