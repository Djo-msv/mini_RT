#include "miniRT.h"

t_vec vec_scale(t_vec v, float s)
{
	t_vec result;
	result.i = v.i * s;
	result.j = v.j * s;
	result.k = v.k * s;
	return result;
}

void	recalculate_ray_direction(t_setting_cam *scene)
{
	int		x;
	int		y;
	t_vec	pixel_center;

	x = 0;
	while (x != scene->width)
	{
		y = 0;
		while (y != scene->height)
		{
			pixel_center = vec_add(
    			vec_add(scene->pixel00_loc, vec_mul(scene->pixel_delta_h, x)),
    			vec_mul(scene->pixel_delta_v, y));
			scene->ray_direction[x][y] = vec_sub(pixel_center, scene->camera_center);
			y++;
		}
		x++;
	}
}


void	angle_camera(t_data *data, float pitch, float yaw)
{
	data->setting_cam.forward = (t_vec){cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw)};
	t_vec	right = normalize(cross(data->setting_cam.forward, create_vec(0, 1, 0)));
	t_vec	up = normalize(cross(right, data->setting_cam.forward));

	// 1. Stocke les vecteurs principaux
	data->setting_cam.viewport_h = vec_scale(right, data->setting_cam.viewport_width);
	data->setting_cam.viewport_v = vec_scale(up, data->setting_cam.viewport_height);

	// 2. Position du coin haut gauche du viewport (avant de tracer les rayons)
	t_vec viewport_center = vec_add(
		data->setting_cam.camera_center,
		vec_scale(data->setting_cam.forward, data->setting_cam.focal_length));

	t_vec half_h = vec_scale(data->setting_cam.viewport_h, 0.5);
	t_vec half_v = vec_scale(data->setting_cam.viewport_v, 0.5);

	data->setting_cam.viewport_upper_left = vec_sub(
	    vec_sub(viewport_center, half_h),
	    half_v);

	// 3. Calcul des deltas entre les pixels
	data->setting_cam.pixel_delta_h = vec_scale(data->setting_cam.viewport_h, 1.0f / data->setting_cam.width);
	data->setting_cam.pixel_delta_v = vec_scale(data->setting_cam.viewport_v, 1.0f / data->setting_cam.height);

	// 4. Position du pixel (0,0)
	t_vec half_delta_h = vec_scale(data->setting_cam.pixel_delta_h, 0.5f);
	t_vec half_delta_v = vec_scale(data->setting_cam.pixel_delta_v, 0.5f);

	data->setting_cam.pixel00_loc = vec_add(
		vec_add(data->setting_cam.viewport_upper_left, half_delta_h),
		half_delta_v);
	data->image.nb_images = 0;
	recalculate_ray_direction(&data->setting_cam);
}
