#ifndef	RAY_TRACING_H
# define RAY_TRACING_H

t_hit	nearest_cylinder(t_scene scene, t_ray ray);
t_hit	nearest_sphere(t_scene scene, t_ray ray);
t_hit	nearest_plane(t_scene scene, t_ray ray);

#endif
