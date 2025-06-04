#include "miniRT.h"

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
