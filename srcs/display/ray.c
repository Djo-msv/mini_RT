#include "miniRT.h"

mlx_color	ray_color(t_ray ray)
{
	(void)ray;
	return ((mlx_color){ .rgba = 0x00FF00FF });
}

mlx_color	render(t_data *data, int x, int y)
{
	t_setting_cam	camera;

	camera = data->setting_cam;
	return (ray_color(create_ray(camera.camera_center, camera.ray_direction[x][y])));
}
