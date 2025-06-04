#include "miniRT.h"

void	average_pixel(mlx_color *n_pixel, mlx_color o_pixel, float coef_new_p, float coef_old_p)
{
	float	tmp;

	tmp = (n_pixel->r * coef_old_p) + (o_pixel.r * coef_new_p);
	n_pixel->r = (uint8_t)(tmp + 0.5f); 
	tmp = (n_pixel->g * coef_old_p) + (o_pixel.g * coef_new_p);
	n_pixel->g = (uint8_t)(tmp + 0.5f); 
	tmp = (n_pixel->b * coef_old_p) + (o_pixel.b * coef_new_p);
	n_pixel->b = (uint8_t)(tmp + 0.5f);
}
