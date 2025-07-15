#ifndef IMAGE_H
# define IMAGE_H

typedef struct s_image
{
	size_t		nb_images;
	double		coef_new_p;
	double		coef_old_p;
	int			resolution;
	bool		antialiasing;

	t_fcolor	*buf_img;
//	t_fcolor	*old_img;
	mlx_color	*mlx_img;
}	t_render_image
__attribute__((aligned(1)));

#endif
