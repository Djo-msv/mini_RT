#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_ray
{
    t_vec origin;
    t_vec direction;
}	t_ray;

t_vec	vec_add(t_vec vec1, t_vec vec2);
t_vec	vec_sub(t_vec vec1, t_vec vec2);
t_vec	vec_mul(t_vec vec, float mult);
t_vec	vec_div(t_vec vec, float div);
t_vec	vec_cross(t_vec a, t_vec b);
float	scalar_product(t_vec a, t_vec b);
t_vec	normalize(t_vec v);
float	length(t_vec v);
t_vec	cross(t_vec a, t_vec b);
t_vec	vec_scale(t_vec v, float s);
t_vec	vec_neg(t_vec v);

t_ray	create_ray(t_vec origin, t_vec direction);

#endif
