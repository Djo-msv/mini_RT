#ifndef CAMERA_H
# define CAMERA_H

void	move_camera_down(t_data *data, t_setting_cam *cam);
void	move_camera_up(t_data *data, t_setting_cam *cam);
void	move_camera_right(t_data *data, t_setting_cam *cam);
void	move_camera_left(t_data *data, t_setting_cam *cam);
void	move_camera_backward(t_data *data, t_setting_cam *cam);
void	move_camera_forward(t_data *data, t_setting_cam *cam);

void	rotate_camera(t_data *data, float pitch, float yaw);

void	setup_camera_setting(t_data *data);
void	calcule_res(t_data *data, t_setting_cam *cam);
void	calculate_ray_direction(t_setting_cam *scene);

void	angle_camera(t_data *data, float pitch, float yaw);

#endif
