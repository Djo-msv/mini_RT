#ifndef RENDER_H
# define RENDER_H

float	hit_sphere(t_coordinate center, double radius, t_ray r);

float	hit_plane(t_coordinate c, t_vec normal, t_ray r);

float hit_cylinder(t_cylinder *cy, float rad, t_ray r);

void	average_pixel(t_fcolor *n_pixel, t_fcolor o_pixel, float coef_new_p, float coef_old_p);
void	sampling(t_fcolor *n_pixel, t_fcolor o_pixel, double coef_new_p, double coef_old_p);

void	render(t_data *data, t_fcolor *pixel, t_vec ray_direction);

void	handle_low_resolution(t_data *data, int x, int y, int resolution);

void	setup_camera_setting(t_data *data);
void	calcule_res(t_data *data, t_setting_cam *cam);
void	recalculate_ray_direction(t_setting_cam *scene);


t_ray	get_antialiasing(t_data *data, t_vec base_ray);

void	angle_camera(t_data *data, float pitch, float yaw);

void fcolor_to_mlxcolor(t_data *data, t_fcolor *src, mlx_color *dst, size_t n);
t_fcolor add_color(t_fcolor c1, t_fcolor c2);
t_fcolor scale_mlx_color(t_fcolor color, float factor);
t_fcolor scalar_color(t_fcolor c1, t_fcolor c2);

#endif
