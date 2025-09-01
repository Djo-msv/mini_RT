#include "miniRT.h"
/*
void	angle_camera(t_data *data, float pitch, float yaw)
{
	t_vec	forward;
	t_vec	right;
	t_vec	up;

	forward = (t_vec){
		cos(pitch) * sin(yaw),
		sin(pitch),
		cos(pitch) * cos(yaw)
	};
	data->cam.forward = normalize(forward);
	right = normalize(cross(data->setting_cam.forward,
				(t_vec){0.0f, 1.0f, 0.0f}));
	up = cross(right, data->setting_cam.forward);
	data->cam.viewport_h = vec_scale(right,
			data->cam.viewport_width);
	data->cam.viewport_v = vec_scale(up,
			data->setting_cam.viewport_height);
}*/

void	rotate_camera(t_data *data, float pitch, float yaw)
{
//	angle_camera(data, pitch, yaw);
//	calcule_res(data, &data->cam);
	set_camera_ray(data->pool->ray_direction, &data->cam, data->mlx.info);
	(void)yaw;
	(void)pitch;

	data->image.nb_images = 0;
}
