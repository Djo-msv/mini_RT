#include "miniRT.h"

t_vec vec_add(t_vec vec1, t_vec vec2)
{
    return ((t_vec){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_vec vec_sub(t_vec vec1, t_vec vec2)
{
    return ((t_vec){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
}

t_vec vec_mul(t_vec vec, float mult)
{
    return ((t_vec){vec.x * mult, vec.y * mult, vec.z * mult});
}

t_vec vec_div(t_vec vec, float div)
{
    if (div == 0.0f)
        return ((t_vec){0.0f, 0.0f, 0.0f});
    return ((t_vec){vec.x / div, vec.y / div, vec.z / div});
}

t_vec vec_cross(t_vec a, t_vec b) {
    return (t_vec){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x};
}

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

t_vec vec_neg(t_vec v)
{
    return (t_vec){-v.x, -v.y, -v.z};
}
