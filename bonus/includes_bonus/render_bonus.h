/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:01:05 by star              #+#    #+#             */
/*   Updated: 2025/10/01 19:21:14 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H

void		render(t_fcolor *pixel, t_vec ray_direction, t_scene *scene);

t_hit		intersectscene(t_scene scene, t_ray ray, bool direct_light);
t_fcolor	shade_pathtracing_pixel(t_scene scene, t_ray ray);
t_fcolor	shade_raytracing_pixel(t_scene scene, t_ray ray);

void		nearest_obj_bonus(t_scene scene, t_ray ray, t_hit *hit);
t_hit		nearest_obj(t_scene scene, t_ray ray, bool direct_light);
t_hit		nearest_ellipsoid(t_scene scene, t_ray ray);

float		hit_cylinder(t_cylinder *cy, float rad, t_ray r);
float		hit_base_cylinder(t_cylinder *cy, t_vec center, t_ray r);
float		hit_plane(t_vec center, t_vec normal, t_ray r);
float		hit_sphere(t_vec center, float radius, t_ray r);
float		hit_triangle(t_triangle *tr, t_ray r);
float		hit_ellipsoid(t_ellipsoid *e, t_ray r, t_hit *hit);

t_hit		ellipsoid(t_hit hit);
t_hit		cylinder(t_hit hit);
t_hit		sphere(t_scene scene, t_hit hit);
t_hit		plane(t_hit hit);
t_fcolor	c_texture(int x, int y, t_hit hit, t_scene scene);
t_vec		bump_map(t_scene scene, t_hit hit, int x, int y);
void		generate_uv(int *x, int *y, t_hit hit);
float	hit_sphere_heightmap(t_scene scene, t_sphere *sphere, t_ray ray);


t_vec		get_triangle_normal(t_triangle *t);

t_ray		get_antialiasing(t_scene scene, t_vec base_ray);

t_vec		cosine_weighted_hemisphere(t_vec normal);
t_vec		reflect(t_vec v, t_vec n);
void		plastic_light(t_hit	*hit, t_ray *ray, t_fcolor *throughput);
void		miror_light(t_hit	*hit, t_ray *ray, t_fcolor *throughput);
int			assign_material(t_hit hit, t_fcolor value[3],
				bool *direct_light, t_ray *ray);

#endif
