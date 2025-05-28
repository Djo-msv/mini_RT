#include "miniRT.h"

/*
t_vec	get_antialiasing(t_data *data, t_vec base_ray)
{
	t_vec horizontal = {viewport_width, 0, 0};
	t_vec vertical = {0, viewport_height, 0};
	t_vec lower_left = vec_sub(
	vec_sub(
		vec_sub(camera_pos, vec_scale(horizontal, 0.5f)),
		vec_scale(vertical, 0.5f)),
		create_vec(0, 0, focal_length)
	);
    t_vec dir = vec_sub(vec_add(vec_add(lower_left, vec_scale(horizontal, u)),
		vec_scale(vertical, v)),
		camera_pos);
    return (Ray){camera_pos, vec_normalize(dir)};
}*/

t_ray get_antialiasing(t_data *data, t_vec base_ray)
{
	t_setting_cam	cam = data->setting_cam;
	if (!data->image.antialiasing)
		return (create_ray(cam.camera_center, base_ray));
	t_vec dir = normalize(base_ray);

	dir.i += cam.rand_h;
	dir.j += cam.rand_v;
	dir = normalize(dir);
	return create_ray (cam.camera_center, dir);
}
