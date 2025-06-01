#ifndef MATH_RT_H
# define MATH_RT_H

typedef struct s_coordinate
{
	float	x;
	float	y;
	float	z;
}	t_coordinate;

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
}	t_ray;

t_ray	create_ray(t_vec origin, t_vec direction);

float	scalar_product(t_vec a, t_vec b);
t_vec	normalize(t_vec v);
float length(t_vec v);

t_vec	create_vec(float i, float j, float k);
t_vec	vec_add(t_vec vec1, t_vec vec2);
t_vec	vec_sub(t_vec vec1, t_vec vec2);
t_vec	vec_mul(t_vec vec, float mult);
t_vec	vec_div(t_vec vec, float div);

t_vec	cross(t_vec a, t_vec b);
t_vec vec_scale(t_vec v, float s);


#endif
