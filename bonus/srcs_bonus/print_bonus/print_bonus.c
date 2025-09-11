/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:36:04 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:28:04 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	size_of_float(float size)
{
	int	i = 0;

	while (size / 10 >= 10)
	{
		size = size / 10;
		i++;
	}
	return (i);
}

void	print_nb_fps(float fps)
{
	if (fps >= 9999.99)
		printf("│???????│\n");
	else if (fps < 10.0f)
		printf("│  %s%.2f%s │\n", P_RED, fps, P_GREEN);
	else if (fps < 30.0f)
		printf("│ %s%.2f%s │\n", P_YELLOW, fps, P_GREEN);
	else
	{
		int	i = 0;
		int size = size_of_float(fps) + 3;
		ft_putstr("│");
		while (i++ != 3 - ((size + 1) >> 1))
			ft_putchar(' ');
		printf("%.2f", fps);
		fflush(stdout);
		i += size;
		while (i++ != 6)
			ft_putchar(' ');
		ft_putstr("│\n");
	}
}

char	*name_obj(int obj)
{
	if (obj == 0)
		return ("Plane");
	else if (obj == 1)
		return ("Sphere");
	else if (obj == 2)
		return ("Cylinder");
	else if (obj == 3)
		return ("Light");
	else if (obj == 4)
		return ("Triangle");
	else if (obj == 5)
		return ("Ellipsoid");
	return ("None");
}

void	print_info(t_print_info *info)
{
//	(void)info;
//	printf("hello\n");
//	return ;
	if (!info->first_display)
		printf("\033[17A");
	else
		info->first_display = false;
	printf("%s%s┌──FPS──┐\n", P_GREEN, P_BOLD);
	print_nb_fps(info->fps);
	printf("└───────┘%s\n\n", P_NOC);
	printf("display : %d × %d    \n", info->y, info->x);
	printf("resolution : %d  \n", info->resolution);
	if (info->aa)
		printf("AA : %strue %s\n\n", P_GREEN, P_NOC);
	else
		printf("AA : %sfalse%s\n\n", P_RED, P_NOC);
//	printf("%s%s╔══════CAMERA══════╗\n", P_TEAL, P_BOLD);
//	print_cam_info
//	printf("╚══════════════════╝%s\n\n", P_NOC);
	printf("input : %d\n\n", info->nb_input);
	printf("sample : %d\n\n", info->sample);
	printf("select : %s\n\n", name_obj(info->obj));
	if (info->rotate_mode)
		printf("Rotate_mode : %strue %s\n\n", P_GREEN, P_NOC);
	else
		printf("Rotate_mode : %sfalse%s\n\n", P_RED, P_NOC);
	if (info->scale_mode)
		printf("Scale_mode : %strue %s\n", P_GREEN, P_NOC);
	else
		printf("Scale_mode : %sfalse%s\n", P_RED, P_NOC);
}
