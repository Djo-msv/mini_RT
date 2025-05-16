/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:10:14 by nrolland          #+#    #+#             */
/*   Updated: 2025/05/16 20:58:20 by nrolland         ###   ########.fr       */
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

// int	which_object(t_data *d, char *str)
// {
// 	if ()
// }

// int	ft_count()
// {

// }

// int	ft_parse(t_data *d, char *str)
// {
// 	int		i;
// 	int		len;
// 	int		all_len;
// 	char 	**strings;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	all_len = 0;
// 	strings = ft_calloc(ft_count(str), sizeof(char *));
// 	while (i < all_len)
// 	{
// 		while (ft_is_space(str[i]))
// 			i++;
// 		while (!ft_is_space(str[i++]) && str[i] != ',')
// 		{
// 			i++;
// 			len++;
// 		}
// 		strings[j++] = ft_substr(str, i - len, len);
// 	}
// }

int	parse_init(t_data *d, int argc, char **argv)
{
	int	fd;
	char *str;

	if (verif_name(argc, argv))
		return (1);
	(void)d;
	fd = open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		// ft_parse(d, str);
		printf("%s\n", str);
		free(str);
		str = get_next_line(fd);
	}
	printf("%s\n", str);
	close (fd);
	return (0);
}
