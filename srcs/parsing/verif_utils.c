/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:48:36 by nrolland          #+#    #+#             */
/*   Updated: 2025/05/26 19:25:31 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	verif_str(char *str)
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

int	verif_fvalue(float min, float max, float value)
{
	if (value < min || value > max)
			return (1);
	return (0);
}
