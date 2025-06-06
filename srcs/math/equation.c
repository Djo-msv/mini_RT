#include "miniRT.h"

float scalar_product(t_vec a, t_vec b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec normalize(t_vec v)
{
	t_vec unit;
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

    if (length == 0)
	{
        t_vec zero = {0, 0, 0};
        return zero;
    }

    unit.x = v.x / length;
    unit.y = v.y / length;
    unit.z = v.z / length;
    return (unit);
}

float length(t_vec v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec	cross(t_vec a, t_vec b)
{
	t_vec result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}

t_vec vec_scale(t_vec v, float s)
{
	t_vec result;
	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;
	return result;
}
