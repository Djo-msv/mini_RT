#include "miniRT.h"

void	average_pixel(t_fcolor *n_pixel, t_fcolor o_pixel, float coef_new_p, float coef_old_p)
{
	float	tmp;

	tmp = (n_pixel->r * coef_old_p) + (o_pixel.r * coef_new_p);
	n_pixel->r = tmp; 
	tmp = (n_pixel->g * coef_old_p) + (o_pixel.g * coef_new_p);
	n_pixel->g = tmp; 
	tmp = (n_pixel->b * coef_old_p) + (o_pixel.b * coef_new_p);
	n_pixel->b = tmp;
}
