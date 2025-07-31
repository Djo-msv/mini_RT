/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:35:48 by star              #+#    #+#             */
/*   Updated: 2025/07/31 20:34:46 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	get_antialiasing(t_scene scene, t_vec base_ray)
{
	t_cam	cam;
	t_vec	dir;

	cam = scene.camera;
	dir = base_ray;
	if (!cam.aa)
		return (create_ray(cam.coordinate, base_ray));
	dir = base_ray;
	dir.x += cam.rand_h;
	dir.y += cam.rand_v;
	dir = normalize(dir);
	return (create_ray(cam.coordinate, dir));
}
