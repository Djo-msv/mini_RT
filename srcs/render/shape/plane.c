/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:32:58 by star              #+#    #+#             */
/*   Updated: 2025/06/10 16:22:26 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float hit_plane(t_vec c, t_vec normal, t_ray r)
{
	float	t;
	float	denominator;

	denominator = scalar_product(r.direction, normal);
	t = scalar_product(vec_sub((t_vec){c.x, c.y, c.z}, r.origin), normal) / denominator;
	if (t >= 0.0)
		return (t);
	return (-1.0);
}

