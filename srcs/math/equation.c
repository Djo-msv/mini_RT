#include "miniRT.h"

float scalar_product(t_vec a, t_vec b)
{
    return a.i * b.i + a.j * b.j + a.k * b.k;
}

t_vec normalize(t_vec v)
{
	t_vec unit;
    float length = sqrt(v.i * v.i + v.j * v.j + v.k * v.k);

    if (length == 0)
	{
        t_vec zero = {0, 0, 0};
        return zero;
    }

    unit.i = v.i / length;
    unit.j = v.j / length;
    unit.k = v.k / length;
    return (unit);
}

float length(t_vec v)
{
	return sqrtf(v.i * v.i + v.j * v.j + v.k * v.k);
}

t_vec	cross(t_vec a, t_vec b)
{
	t_vec result;
	result.i = a.j * b.k - a.k * b.j;
	result.j = a.k * b.i - a.i * b.k;
	result.k = a.i * b.j - a.j * b.i;
	return result;
}

t_vec vec_scale(t_vec v, float s)
{
	t_vec result;
	result.i = v.i * s;
	result.j = v.j * s;
	result.k = v.k * s;
	return result;
}
