#include "miniRT.h"

t_ray	create_ray(t_vec origin, t_vec direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_point	creat_point(int x, int y, int z)
{
	t_point pnt;

	pnt.x = x;
	pnt.y = y;
	pnt.z = z;
	return (pnt);
}
