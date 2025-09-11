/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:40:34 by star              #+#    #+#             */
/*   Updated: 2025/07/28 15:52:13 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_fcolor	add_color(t_fcolor c1, t_fcolor c2)
{
	return ((t_fcolor){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b});
}

t_fcolor	scale_mlx_color(t_fcolor color, float factor)
{
	t_fcolor	result;

	result.r = color.r * factor;
	result.g = color.g * factor;
	result.b = color.b * factor;
	return (result);
}

t_fcolor	scalar_color(t_fcolor c1, t_fcolor c2)
{
	return ((t_fcolor){c1.r * c2.r, c1.g * c2.g, c1.b * c2.b});
}

t_fcolor	mlxcolor_to_fcolor(mlx_color color)
{
	return ((t_fcolor){color.r / 255.0f, color.g / 255.0f, color.b / 255.0f});
}

void	fcolor_to_mlxcolor(t_data *d, t_fcolor *s, mlx_color *dst, size_t n)
{
	double	coef_new_p = d->image.coef_new_p;
	double	coef_old_p = d->image.coef_old_p;
	

	for (size_t i = 0; i < n; ++i)
	{
		double rf = s[i].r * 255.0f;
		double gf = s[i].g * 255.0f;
		double bf = s[i].b * 255.0f;

		double r = (uint8_t)(fminf(fmaxf(rf, 0.0f), 255.0f));
		double g = (uint8_t)(fminf(fmaxf(gf, 0.0f), 255.0f));
		double b = (uint8_t)(fminf(fmaxf(bf, 0.0f), 255.0f));
		if (!1)
		{
			dst[i].r = (uint8_t)((r * coef_old_p) + ((double)dst[i].r * coef_new_p));
			dst[i].g = (uint8_t)((g * coef_old_p) + ((double)dst[i].g * coef_new_p));
			dst[i].b = (uint8_t)((b * coef_old_p) + ((double)dst[i].b * coef_new_p));
		}
		else
		{
			dst[i].r = r;
			dst[i].g = g;
			dst[i].b = b;
		}
		dst[i].a = 255;
	}
}
