#include "miniRT.h"

float hit_cylinder(t_cylinder *cy, float rad, t_ray r)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t;
	t_vec	o_c;
	t_vec	d_perpendicular;
	t_vec	o_c_perpendicular;

	cy->normal = normalize(cy->normal);
	o_c = vec_sub(r.origin, (t_vec){cy->coordinate.x, cy->coordinate.y, cy->coordinate.z});
	d_perpendicular = vec_sub(r.direction, vec_mul(cy->normal, scalar_product(r.direction, cy->normal)));
	o_c_perpendicular = vec_sub(o_c, vec_mul(cy->normal, scalar_product(o_c, cy->normal)));
	a = scalar_product(d_perpendicular, d_perpendicular);
	b = 2.0 * scalar_product(d_perpendicular, o_c_perpendicular);
	c = scalar_product(o_c_perpendicular, o_c_perpendicular) - rad * rad;
	delta = b * b - 4.0 * a * c;
	if (delta < 0.0)
		return (-1.0);
	else
		t = ((-b - sqrt(delta)) / (2.0 * a));
	o_c = vec_sub(vec_add(r.origin, vec_mul(r.direction, t)), cy->coordinate);
	float	height;
	height = scalar_product(o_c, cy->normal);
	if (height < -cy->height / 2.0 || height > cy->height / 2.0)
		return (-1.0);
	return (t);
}

float	hit_base_cylinder(t_cylinder *cy, t_vec center, t_ray r)
{
	float	t;

	t = hit_plane(center, cy->normal, r);
	if (length(vec_sub(vec_add(r.origin, vec_mul(r.direction, t)), center)) <= cy->radius)
		return (t);
	return (-1.0);
}