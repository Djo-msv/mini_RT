#include "miniRT.h"

t_vec create_vec(float x, float y, float z)
{
    t_vec vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    return (vec);
}

t_vec vec_add(t_vec vec1, t_vec vec2)
{
    return (create_vec(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z));
}

t_vec vec_sub(t_vec vec1, t_vec vec2)
{
    return (create_vec(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z));
}

t_vec vec_mul(t_vec vec, float mult)
{
    return (create_vec(vec.x * mult, vec.y * mult, vec.z * mult));
}

t_vec vec_div(t_vec vec, float div)
{
    if (div == 0.0f)
    {
        fprintf(stderr, "Erreur : division par zéro dans vec_div\n");
        return (create_vec(0.0f, 0.0f, 0.0f));
    }
    return (create_vec(vec.x / div, vec.y / div, vec.z / div));
}

t_vec vec_cross(t_vec a, t_vec b) {
    return create_vec(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
}
