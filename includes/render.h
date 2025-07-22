#ifndef RENDER_H
# define RENDER_H

void		render(t_data *data, t_fcolor *pixel, t_vec ray_direction);

t_hit		intersectScene(t_data *data, t_ray ray);
t_fcolor	shade_pathtracing_pixel(t_data *data, t_ray ray);
t_fcolor	shade_raytracing_pixel(t_data *data, t_ray ray);


t_hit	nearest_obj(t_data *data, t_ray ray);
t_hit	nearest_ellipsoid(t_data *data, t_ray ray);
t_hit	nearest_cylinder(t_data *data, t_ray ray);

float	hit_cylinder(t_cylinder *cy, float rad, t_ray r);
float	hit_base_cylinder(t_cylinder *cy, t_vec center, t_ray r);
float	hit_plane(t_vec center, t_vec normal, t_ray r);
float	hit_sphere(t_vec center, double radius, t_ray r);
float 	hit_triangle(t_triangle *tr, t_ray r);
float	hit_ellipsoid(t_ellipsoid *e, t_ray r);

t_hit	plane(t_hit hit);
t_hit	sphere(t_data *data, t_hit hit);
t_hit	cylinder(t_hit hit);
t_hit	ellipsoid(t_hit hit);

t_vec	get_triangle_normal(t_triangle *t);

t_ray get_antialiasing(t_data *data, t_vec base_ray);

#endif
