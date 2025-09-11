/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:01:05 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:22:51 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H

void		render(t_fcolor *pixel, t_vec ray_direction, t_scene *scene);

t_hit		intersectscene(t_scene scene, t_ray ray, bool direct_light);
t_fcolor	shade_pathtracing_pixel(t_scene scene, t_ray ray);
t_fcolor	shade_raytracing_pixel(t_scene scene, t_ray ray);

t_hit	nearest_obj(t_scene scene, t_ray ray, bool direct_light);
t_hit	nearest_ellipsoid(t_scene scene, t_ray ray);

float	hit_cylinder(t_cylinder *cy, float rad, t_ray r);
float	hit_base_cylinder(t_cylinder *cy, t_vec center, t_ray r);
float	hit_plane(t_vec center, t_vec normal, t_ray r);
float	hit_sphere(t_vec center, double radius, t_ray r);
float 	hit_triangle(t_triangle *tr, t_ray r);
float	hit_ellipsoid(t_ellipsoid *e, t_ray r, t_hit *hit);

t_hit	    ellipsoid(t_hit hit);
t_hit	    cylinder(t_hit hit);
t_hit	    sphere(t_scene scene, t_hit hit);
t_hit	    plane(t_hit hit);
t_fcolor	c_texture(int *x, int *y, t_hit hit, t_scene scene);
t_vec	    bump_map(t_scene scene, t_hit hit, int x, int y);

t_vec	get_triangle_normal(t_triangle *t);

t_ray get_antialiasing(t_scene scene, t_vec base_ray);

#endif
