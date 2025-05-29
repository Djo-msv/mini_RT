/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:10:14 by nrolland          #+#    #+#             */
/*   Updated: 2025/05/29 18:14:49 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	verif_name(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
	{
		ft_putstr_fd("Error\nNeed one scene in format *.rt\n", 2);
		return (1);
	}
	while (ft_isascii(argv[1][i]) && argv[1][i] != '.')
		i++;
	if (ft_strncmp(".rt\0", argv[1] + i, 4))
	{
		ft_putstr_fd("Error\nNeed format *.rt\n", 2);
		return (1);
	}
	if (access(argv[1], F_OK) == -1)
	{
		ft_putstr_fd("Error\nFile not found\n", 2);
		return (1);
	}
	return (0);
}

int	parse(t_data *d, int argc, char **argv)
{
	int	fd;

	if (verif_name(argc, argv))
		return (1);
	(void)d;
	fd = open(argv[1], O_RDONLY);
	if (creat_scene(d, fd))
		return (1);
	close(fd);
	return (0);
}
