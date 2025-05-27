#include "miniRT.h"

t_vec create_vec(float i, float j, float k)
{
    t_vec vec;

    vec.i = i;
    vec.j = j;
    vec.k = k;
    return (vec);
}

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
    {
        fprintf(stderr, "Erreur : division par zéro dans vec_div\n");
        return (create_vec(0.0f, 0.0f, 0.0f));
    }
    return (create_vec(vec.i / div, vec.j / div, vec.k / div));
}

Vec3 vec_cross(t_vec a, t_vec b) {
    return (Vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
