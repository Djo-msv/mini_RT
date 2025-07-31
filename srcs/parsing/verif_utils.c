/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:48:36 by nrolland          #+#    #+#             */
/*   Updated: 2025/07/31 20:00:02 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	verif_file(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (ft_isascii(str[i]) && str[i] != '.')
		i++;
	if (ft_strncmp(".jpg\0", str + i, 5)
		&& ft_strncmp(".png\0", str + i, 5)
		&& ft_strncmp(".bmp\0", str + i, 5))
		return (1);
	if (access(str, F_OK) == -1)
		return (1);
	return (0);
}

int	verif_str(char *str)
{
	int	i;
	int	v;

	i = 0;
	v = 0;
	if (!str)
		return (1);
	if ((!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-'))
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (!ft_isdigit(str[i - 1]) || !ft_isdigit(str[i + 1]))
				return (1);
			v++;
		}
		if ((!ft_isdigit(str[i]) && str[i] != '.') || v == 2)
			return (1);
		i++;
	}
	return (0);
}

int	verif_fvalue(float min, float max, float value)
{
	if (value < min || value > max)
		return (1);
	return (0);
}
