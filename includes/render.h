#ifndef RENDER_H
# define RENDER_H

typedef struct	s_hit
{
	float	t;
	void	*obj;
	int		type;
	int		material;
	t_vec	position;
	t_vec	normal;
	t_fcolor	color;
}	t_hit
__attribute__((aligned(1)));

void		render(t_data *data, t_fcolor *pixel, t_vec ray_direction);

t_hit		intersectScene(t_data *data, t_ray ray);
t_fcolor		shade_pixel(t_data *data, t_ray ray);

t_hit	nearest_obj(t_data *data, t_ray ray);

float hit_cylinder(t_cylinder *cy, float rad, t_ray r);
float hit_plane(t_vec center, t_vec normal, t_ray r);
float hit_sphere(t_vec center, double radius, t_ray r);

#endif
