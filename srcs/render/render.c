#include "miniRT.h"

mlx_color	ray_color(t_data *data, t_ray ray)
{
	float	t = -1;
	float	old_t = 0;
	mlx_color	pixel;
	t_scene		scene = data->scene;
	t_list		*tmp = scene.sphere;
	t_sphere 	*sphere;

	while (tmp)
	{
		sphere = (t_sphere *)tmp->content;
		t = hit_sphere(sphere->coordinate, sphere->diameter, ray);
//		if (t != -1.0f)
//			printf("%f - %f\n", t, old_t);
		if (t > 0.0f && (t < old_t || old_t == 0))
		{
			t_vec point = vec_add(ray.origin, vec_mul(ray.direction, t));
			t_vec normal = normalize(vec_sub(point, (t_vec){sphere->coordinate.x, sphere->coordinate.y, sphere->coordinate.z}));
			pixel.r = (uint8_t)(255.0f * 0.5f * (normal.i + 1.0f));
			pixel.g = (uint8_t)(255.0f * 0.5f * (normal.j + 1.0f));
			pixel.b = (uint8_t)(255.0f * 0.5f * (normal.k + 1.0f));
			pixel.a = 255;
			old_t = t;
		}
		tmp = tmp->next;
	}
	if (old_t > 0.0f)
	{
		return (pixel);	
	}
	return ((mlx_color){ .rgba = 0xFFFFFFFF });
}

mlx_color	render(t_data *data, int x, int y)
{
	t_setting_cam	camera;

	camera = data->setting_cam;
	return (ray_color(data, get_antialiasing(data, camera.ray_direction[x][y])));
}
