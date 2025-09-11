/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:00:55 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:22:46 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RAY_TRACING_BONUS_H
# define RAY_TRACING_BONUS_H

t_hit	nearest_cylinder(t_scene scene, t_ray ray);
t_hit	nearest_sphere(t_scene scene, t_ray ray);
t_hit	nearest_plane(t_scene scene, t_ray ray);

#endif
