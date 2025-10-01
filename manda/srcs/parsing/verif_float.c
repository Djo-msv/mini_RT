/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:05:22 by nrolland          #+#    #+#             */
/*   Updated: 2025/10/01 19:21:14 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_decimal(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == '.')
			return (1);
		i++;
	}
	return (0);
}

int	verif_int(char *str, char *max)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (verif_str(str))
		return (1);
	if (str[i] == '-')
		return (1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] == '.')
		i--;
	j = ft_strlen(str + i);
	if (is_decimal(&str[i], j))
		return (1);
	if (j < 3)
		return (0);
	if (j > 3)
		return (1);
	if (ft_strncmp(&str[i], max, j) > 0)
		return (1);
	return (0);
}

static int	subtraction(char *str, int len)
{
	int	i;

	i = 0;
	if (!is_decimal(str, len))
		return (0);
	while (str[len] == '0')
	{
		len--;
		i++;
	}
	return (i);
}

int	verfi_float(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (verif_str(str))
		return (1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] == '.')
		i--;
	j = ft_strlen(str + i);
	j = j - subtraction(&str[i], j - 1);
	if (!is_decimal(&str[i], j) && j > 7)
		return (1);
	if (j > 8)
		return (1);
	return (0);
}
