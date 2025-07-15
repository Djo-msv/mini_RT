#include "miniRT.h"

void	angle_camera(t_data *data, float pitch, float yaw)
{
	t_vec forward = (t_vec){
		cos(pitch) * sin(yaw),
		sin(pitch),
		cos(pitch) * cos(yaw)
	};
	data->setting_cam.forward = normalize(forward);

	t_vec right = normalize(cross(data->setting_cam.forward, (t_vec){0.0f, 1.0f, 0.0f}));
	t_vec up = cross(right, data->setting_cam.forward);
	data->setting_cam.viewport_h = vec_scale(right, data->setting_cam.viewport_width);
	data->setting_cam.viewport_v = vec_scale(up, data->setting_cam.viewport_height);
}

void	rotate_camera(t_data *data, float pitch, float yaw)
{
	angle_camera(data, pitch, yaw);
	calcule_res(data, &data->setting_cam);

	threads_ray_direction(data);
	data->image.nb_images = 0;
}
