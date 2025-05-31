#ifndef RENDER_H
# define RENDER_H

float hit_sphere(t_coordinate center, double radius, t_ray r);

void	average_pixel(mlx_color *n_pixel, mlx_color o_pixel, float coef_new_p, float coef_old_p);

mlx_color	render(t_data *data, int x, int y);

void	handle_low_resolution(t_data *data, int x, int y, int resolution);

void	setup_camera_setting(t_data *data);
void	calcule_res(t_data *data, t_setting_cam *cam);
void	recalculate_ray_direction(t_setting_cam *scene);


t_ray get_antialiasing(t_data *data, t_vec base_ray);

void	angle_camera(t_data *data, float pitch, float yaw);

#endif
