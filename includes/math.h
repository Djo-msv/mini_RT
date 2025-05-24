#ifndef MATH_H
# define MATH_H

# include "miniRT.h"

typedef struct s_vec
{
	float	i;
	float	j;
	float	k;
}	t_vec;

typedef struct s_ray
{
    t_vec origin;
    t_vec direction;
} t_ray;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

t_vec	create_vec(float i, float j, float k);

t_point	create_point(float x, float y, float z);

t_vec	vec_add(t_vec vec1, t_vec vec2);
t_vec	vec_sub(t_vec vec1, t_vec vec2);
t_vec	vec_mul(t_vec vec, float mult);
t_vec	vec_div(t_vec vec, float div);

t_ray	create_ray(t_vec origin, t_vec direction);

#endif
