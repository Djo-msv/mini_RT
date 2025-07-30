#include "miniRT.h"

/*
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
*/
void	sampling(t_data *data)
{
	int width = data->mlx.info.width;
	double coef_new_p = data->image.coef_new_p;
	double coef_old_p = data->image.coef_old_p;
	t_fcolor	*buf_img = data->image.buf_img;
	t_fcolor	*buf_thread = data->pool->buffer_b;

	for (int y = 0; y < (data->mlx.info.height); y++)
	{
		for (int x = 0; x < width; x++)
		{
			double r = fmin(fmax((*buf_thread).r * 255.0, 0.0), 255.0);
			double g = fmin(fmax((*buf_thread).g * 255.0, 0.0), 255.0);
			double b = fmin(fmax((*buf_thread).b * 255.0, 0.0), 255.0);

			(*buf_img).r = ((r * coef_old_p) + ((*buf_img).r * coef_new_p));
			(*buf_img).g = ((g * coef_old_p) + ((*buf_img).g * coef_new_p));
			(*buf_img).b = ((b * coef_old_p) + ((*buf_img).b * coef_new_p));
			buf_thread++;
			buf_img++;
		}
	}
}
