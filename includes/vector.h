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

#endif
