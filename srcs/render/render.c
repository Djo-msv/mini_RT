#include "miniRT.h"

mlx_color	ray_color(t_ray ray)
{
	mlx_color	pixel;
	float t = hit_sphere(create_vec(0,0,-1), 0.5, ray);
	if (t > 0.0f)
	{
		t_vec point = vec_add(ray.origin, vec_mul(ray.direction, t));
		t_vec normal = normalize(vec_sub(point, create_vec(0, 0, -1)));
		pixel.r = (uint8_t)(255.0f * 0.5f * (normal.i + 1.0f));
		pixel.g = (uint8_t)(255.0f * 0.5f * (normal.j + 1.0f));
		pixel.b = (uint8_t)(255.0f * 0.5f * (normal.k + 1.0f));
		pixel.a = 255;
		return (pixel);	
	}
	return ((mlx_color){ .rgba = 0xFFFFFFFF });
}

mlx_color	render(t_data *data, int x, int y)
{
	t_setting_cam	camera;

	camera = data->setting_cam;
	return (ray_color(get_antialiasing(data, camera.ray_direction[x][y])));
}
