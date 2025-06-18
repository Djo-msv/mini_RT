#include "miniRT.h"

float hit_sphere(t_vec center, double radius, t_ray r)
{
    t_vec oc = vec_sub((t_vec){center.x, center.y, center.z}, r.origin);
    float a = scalar_product(r.direction, r.direction);
    float b = scalar_product(r.direction, oc);
    float c = scalar_product(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;

    if (discriminant < 0.0)
        return -1.0;
        else
        return (b - sqrt(discriminant)) / (a);
}
