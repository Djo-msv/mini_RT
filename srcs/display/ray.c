#include "miniRT.h"

float scalar_product(t_vec a, t_vec b)
{
    return a.i * b.i + a.j * b.j + a.k * b.k;
}

t_vec normalize(t_vec v)
{
	t_vec unit;
    float length = sqrt(v.i * v.i + v.j * v.j + v.k * v.k);

    if (length == 0)
	{
        t_vec zero = {0, 0, 0};
        return zero;
    }

    unit.i = v.i / length;
    unit.j = v.j / length;
    unit.k = v.k / length;
    return (unit);
}

float hit_sphere(t_vec center, double radius, t_ray r) {
    t_vec oc = vec_sub(center, r.origin);
    float a = scalar_product(r.direction, r.direction);
    float b = scalar_product(r.direction, oc);
    float c = scalar_product(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;

    if (discriminant < 0.0)
        return -1.0;
	else
        return (b - sqrt(discriminant)) / (a);
}

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
	//if (x == 0 && y == 0)
	//	printf("%f\n", camera.ratio);
	return (ray_color(create_ray(camera.camera_center, camera.ray_direction[x][y])));
}
