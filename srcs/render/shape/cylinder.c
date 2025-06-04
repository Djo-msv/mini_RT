#include "miniRT.h"

float hit_cylinder(t_cylinder *cy, float rad, t_ray r)
{
	float	a;
	float	b;
	float	c;
	float	delta;
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
		return ((-b - sqrt(delta)) / (2.0 * a));
}
