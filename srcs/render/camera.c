#include "miniRT.h"

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
	t_vec forward = (t_vec){
		cos(pitch) * sin(yaw),
		sin(pitch),
		cos(pitch) * cos(yaw)
	};
	data->setting_cam.forward = normalize(forward);

	t_vec right = normalize(cross(data->setting_cam.forward, create_vec(0, 1, 0)));
	t_vec up = cross(right, data->setting_cam.forward);  // pas besoin de normaliser up ici

	data->setting_cam.viewport_h = vec_scale(right, data->setting_cam.viewport_width);
	data->setting_cam.viewport_v = vec_scale(up, data->setting_cam.viewport_height);
}

void	rotate_camera(t_data *data, float pitch, float yaw)
{
	angle_camera(data, pitch, yaw);
	calcule_res(data, &data->setting_cam);

	printf("%f - %f\n", pitch, yaw);
	recalculate_ray_direction(&data->setting_cam);
	data->image.nb_images = 0;
}
