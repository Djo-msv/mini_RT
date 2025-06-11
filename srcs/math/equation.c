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

t_vec vec_neg(t_vec v)
{
    return (t_vec){-v.i, -v.j, -v.k};
}

uint8_t clamp(int x)
{
    if (x > 255) return 255;
    if (x < 0) return 0;
    return x;
}

uint8_t clamp_float(float value)
{
    if (value < 0.0f) return 0;
    if (value > 255.0f) return 255;
    return (uint8_t)(value + 0.5f);
}

t_fcolor add_color(t_fcolor c1, t_fcolor c2)
{
	return ((t_fcolor){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b});
}

t_fcolor scale_mlx_color(t_fcolor color, float factor)
{
    t_fcolor result;

    result.r = color.r * factor;
    result.g = color.g * factor;
    result.b = color.b * factor;
    return result;
}

t_fcolor scalar_color(t_fcolor c1, t_fcolor c2)
{
	return ((t_fcolor){c1.r * c2.r, c1.g * c2.g, c1.b * c2.b});
}

float vec_dot(t_vec a, t_vec b)
{
    return a.i * b.i + a.j * b.j + a.k * b.k;
}

void fcolor_to_mlxcolor(t_fcolor *src, mlx_color *dst, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        float rf = src[i].r * 255.0f;
        float gf = src[i].g * 255.0f;
        float bf = src[i].b * 255.0f;

        uint8_t r = (uint8_t)(fminf(fmaxf(rf, 0.0f), 255.0f));
        uint8_t g = (uint8_t)(fminf(fmaxf(gf, 0.0f), 255.0f));
        uint8_t b = (uint8_t)(fminf(fmaxf(bf, 0.0f), 255.0f));

        #if MLX_BYTEORDER == MLX_LITTLE_ENDIAN
            dst[i].r = r;
            dst[i].g = g;
            dst[i].b = b;
            dst[i].a = 255;
        #else
            dst[i].r = r;
            dst[i].g = g;
            dst[i].b = b;
            dst[i].a = 255;
        #endif
    }
}
