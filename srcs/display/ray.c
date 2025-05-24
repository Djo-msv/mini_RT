#include "miniRT.h"

float scalar_product(t_vec a, t_vec b)
{
    return a.i * b.i + a.j * b.j + a.k * b.k;
}

bool	hit_sphere(t_vec center, float radius, t_ray r) {
    t_vec oc = vec_sub(center, r.origin);
    float a = scalar_product(r.direction, r.direction);
    float b = -2.0 * scalar_product(r.direction, oc);
    float c = scalar_product(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

mlx_color	ray_color(t_ray ray)
{
	if (hit_sphere(create_vec(0,0,-1), 0.5, ray))
    	return ((mlx_color){ .rgba = 0xFF0000FF });
	return ((mlx_color){ .rgba = 0xFFFFFFFF });
}

mlx_color	render(t_data *data, int x, int y)
{
	t_setting_cam	camera;

	camera = data->setting_cam;
	//if (x == 0 && y == 0)
	//	printf("%f\n", camera.ratio);
	return (ray_color(create_ray(camera.camera_center, camera.ray_direction[x][y])));
}
