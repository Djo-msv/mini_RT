/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:24:55 by star              #+#    #+#             */
/*   Updated: 2025/07/22 15:24:57 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray get_antialiasing(t_data *data, t_vec base_ray)
{
	t_setting_cam	cam = data->setting_cam;
	if (!data->image.antialiasing)
		return (create_ray(cam.camera_center, base_ray));
	t_vec dir = normalize(base_ray);

	dir.x += cam.rand_h;
	dir.y += cam.rand_v;
	dir = normalize(dir);
	return create_ray (cam.camera_center, dir);
}
