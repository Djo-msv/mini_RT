/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:10:14 by nrolland          #+#    #+#             */
/*   Updated: 2025/10/02 17:11:32 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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
	int	line;

	if (NB_THREAD <= 0 || SIZE_CHUNK <= 0 || MAX_RES_W < 400 || MAX_RES_H < 400)
		return (1);
	if (verif_name(argc, argv))
		return (1);
	(void)d;
	fd = open(argv[1], O_RDONLY);
	line = creat_scene(d, fd);
	if (line)
	{
		ft_printfd(2, "at line : %d\n", line);
		return (1);
	}
	close(fd);
	return (0);
}
