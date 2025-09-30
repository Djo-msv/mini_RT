/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:32:58 by star              #+#    #+#             */
/*   Updated: 2025/09/30 17:25:33 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

float	hit_plane(t_vec c, t_vec normal, t_ray r)
{
	float	t;
	float	denominator;

	denominator = scalar_product(r.direction, normal);
	if (fabs(denominator) < 1e-6)
		return (-1.0);
	t = scalar_product(vec_sub(c, r.origin), normal) / denominator;
	if (t >= 0.0)
		return (t);
	return (-1.0);
}
