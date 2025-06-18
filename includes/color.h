#ifndef COLOR_H
# define COLOR_H

void		fcolor_to_mlxcolor(t_data *data, t_fcolor *src, mlx_color *dst, size_t n);
t_fcolor	scalar_color(t_fcolor c1, t_fcolor c2);
t_fcolor	scale_mlx_color(t_fcolor color, float factor);
t_fcolor	add_color(t_fcolor c1, t_fcolor c2);
t_fcolor	mlxcolor_to_fcolor(mlx_color color);

#endif
