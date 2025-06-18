#include "miniRT.h"

t_vec vec_add(t_vec vec1, t_vec vec2)
{
    return (create_vec(vec1.i + vec2.i, vec1.j + vec2.j, vec1.k + vec2.k));
}

t_vec vec_sub(t_vec vec1, t_vec vec2)
{
    return (create_vec(vec1.i - vec2.i, vec1.j - vec2.j, vec1.k - vec2.k));
}

t_vec vec_mul(t_vec vec, float mult)
{
    return (create_vec(vec.i * mult, vec.j * mult, vec.k * mult));
}

t_vec vec_div(t_vec vec, float div)
{
    if (div == 0.0f)
        return (create_vec(0.0f, 0.0f, 0.0f));
    return (create_vec(vec.i / div, vec.j / div, vec.k / div));
}

t_vec vec_cross(t_vec a, t_vec b) {
    return create_vec(
        a.j * b.k - a.k * b.j,
        a.k * b.i - a.i * b.k,
        a.i * b.j - a.j * b.i);
}

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

t_vec vec_neg(t_vec v)
{
    return (t_vec){-v.i, -v.j, -v.k};
}
