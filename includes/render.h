#ifndef RENDER_H
# define RENDER_H

void		render(t_fcolor *pixel, t_vec ray_direction, t_scene scene);

t_hit		intersectScene(t_scene scene, t_ray ray, bool direct_light);
t_fcolor	shade_pathtracing_pixel(t_scene scene, t_ray ray);
t_fcolor	shade_raytracing_pixel(t_data *data, t_ray ray);


t_hit	nearest_obj(t_scene scene, t_ray ray, bool direct_light);

float	hit_cylinder(t_cylinder *cy, float rad, t_ray r);
float	hit_base_cylinder(t_cylinder *cy, t_vec center, t_ray r);
float	hit_plane(t_vec center, t_vec normal, t_ray r);
float	hit_sphere(t_vec center, double radius, t_ray r);
float 	hit_triangle(t_triangle *tr, t_ray r);
float	hit_ellipsoid(t_ellipsoid *e, t_ray r);

t_vec	get_triangle_normal(t_triangle *t);

t_ray get_antialiasing(t_scene scene, t_vec base_ray);

#endif
