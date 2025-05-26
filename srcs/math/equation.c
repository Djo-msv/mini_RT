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
