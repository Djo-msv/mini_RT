#ifndef CAMERA_H
# define CAMERA_H

void	rotate_camera(t_camera *cam, float pitch, float roll, float yaw);
void	set_camera_ray(t_vec *ray_direction, t_camera *camera, mlx_window_create_info info);

#endif
