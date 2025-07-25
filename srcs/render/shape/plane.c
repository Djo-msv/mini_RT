/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:32:58 by star              #+#    #+#             */
/*   Updated: 2025/07/25 19:35:21 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float hit_plane(t_vec c, t_vec normal, t_ray r)
{
	float	t;
	float	denominator;

	denominator = scalar_product(r.direction, normal);
	t = scalar_product(vec_sub(c, r.origin), normal) / denominator;
	if (t >= 0.0)
		return (t);
	return (-1.0);
}
