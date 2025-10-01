/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_average_pixel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:29:01 by star              #+#    #+#             */
/*   Updated: 2025/10/01 19:21:14 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	average_pixel(t_fcolor *n_pixel, t_fcolor o_pixel,
	float coef_new_p, float coef_old_p)
{
	float	tmp;

	tmp = (n_pixel->r * coef_old_p) + (o_pixel.r * coef_new_p);
	n_pixel->r = tmp;
	tmp = (n_pixel->g * coef_old_p) + (o_pixel.g * coef_new_p);
	n_pixel->g = tmp;
	tmp = (n_pixel->b * coef_old_p) + (o_pixel.b * coef_new_p);
	n_pixel->b = tmp;
}

void	sampling(t_fcolor *o_pixel, t_fcolor n_pixel,
	float coef_new_p, float coef_old_p)
{
	float	tmp;

	if (coef_new_p == 0.0)
	{
		*o_pixel = n_pixel;
		return ;
	}
	tmp = (n_pixel.r * coef_old_p) + (o_pixel->r * coef_new_p);
	o_pixel->r = tmp;
	tmp = (n_pixel.g * coef_old_p) + (o_pixel->g * coef_new_p);
	o_pixel->g = tmp;
	tmp = (n_pixel.b * coef_old_p) + (o_pixel->b * coef_new_p);
	o_pixel->b = tmp;
}
