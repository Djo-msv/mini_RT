#ifndef RENDER_H
# define RENDER_H

typedef struct	s_hit
{
	float	t;
	void	*obj;
	int		type;
}				t_hit;

float	hit_sphere(t_coordinate center, double radius, t_ray r);

float	hit_plane(t_coordinate c, t_vec normal, t_ray r);

float hit_cylinder(t_cylinder *cy, float rad, t_ray r);

void	average_pixel(mlx_color *n_pixel, mlx_color o_pixel, float coef_new_p, float coef_old_p);

mlx_color	render(t_data *data, int x, int y);

void	handle_low_resolution(t_data *data, int x, int y, int resolution);

void	setup_camera_setting(t_data *data);

t_ray	get_antialiasing(t_data *data, t_vec base_ray);

#endif
