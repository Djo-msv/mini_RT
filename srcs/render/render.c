#include "miniRT.h"

mlx_color t_color_to_mlx_color(t_color c)
{
    mlx_color result;

    result.r = c.r;
    result.g = c.g;
    result.b = c.b;
    result.a = 255;
    return result;
}

t_vec	coordinate_to_vec(t_coordinate coord)
{
	t_vec vec;

	vec.i = coord.x;
	vec.j = coord.y;
	vec.k = coord.z;
	return vec;
}

t_hit	nearest_cylinder(t_data *data, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_cylinder	*cylinder;
	float		t;
	
	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = data->scene.cylinder;
	while (tmp)
	{
		cylinder = (t_cylinder *)tmp->content;
		t = hit_cylinder(cylinder, cylinder->radius, ray);
		if (t > 0.0f && (t < hit.t || hit.t == 0))
		{
			hit.t = t;
			hit.obj = cylinder;
			hit.type = 2;
		}
		tmp = tmp->next;
	}
	return (hit);
}


t_hit	nearest_plane(t_data *data, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_plane		*plane;
	float		t;
	
	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = data->scene.plane;
	while (tmp)
	{
		plane = (t_plane *)tmp->content;
		t = hit_plane(plane->coordinate, plane->normal, ray);
		if (t > 0.0f && (t < hit.t || hit.t == 0))
		{
			hit.t = t;
			hit.obj = plane;
			hit.type = 0;
		}
		tmp = tmp->next;
	}
	return (hit);
}

t_hit	nearest_light(t_data *data, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_light	*light;
	float		t;
	
	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = data->scene.light;
	while (tmp)
	{
		light = (t_light *)tmp->content;
		t = hit_sphere(light->coordinate, 1.0f, ray);
		if (t > 0.0f && (t < hit.t || hit.t == 0))
		{
			hit.t = t;
			hit.obj = light;
			hit.type = 3;
		}
		tmp = tmp->next;
	}
	return (hit);
}


t_hit	nearest_sphere(t_data *data, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_sphere	*sphere;
	float		t;
	
	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = data->scene.sphere;
	while (tmp)
	{
		sphere = (t_sphere *)tmp->content;
		t = hit_sphere(sphere->coordinate, sphere->radius, ray);
		if (t > 0.0f && (t < hit.t || hit.t == 0))
		{
			hit.t = t;
			hit.obj = sphere;
			hit.type = 1;
		}
		tmp = tmp->next;
	}
	return (hit);
}

t_hit	nearest_obj(t_data *data, t_ray ray)
{
	t_hit	hit;
	t_hit	buf_hit;

	hit = nearest_sphere(data, ray);
	buf_hit = nearest_plane(data, ray);
	if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
		hit = buf_hit;
	buf_hit = nearest_cylinder(data, ray);
	if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
		hit = buf_hit;
	buf_hit = nearest_light(data, ray);
	if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
		hit = buf_hit;
	return (hit);
}

/*
mlx_color	ray_color(t_data *data, t_ray ray)
{
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	mlx_color	pixel;
	t_hit		hit;

	hit = nearest_obj(data, ray);
	if (hit.t <= 0)
		return ((mlx_color){.rgba = 0x000000FF});
	if (hit.type == 0)
	{
		plane = (t_plane *)hit.obj;
		t_vec point = vec_add(ray.origin, vec_mul(ray.direction, hit.t));
		t_vec normal = normalize(vec_sub(point, (t_vec){plane->coordinate.x, plane->coordinate.y, plane->coordinate.z}));
		pixel.r = (plane->color.r * 0.5f * (normal.i + 1.0f));
		pixel.g = (plane->color.g * 0.5f * (normal.j + 1.0f));
		pixel.b = (plane->color.b * 0.5f * (normal.k + 1.0f));
		pixel.a = 255;
	}
	else if (hit.type == 1)
	{
		sphere = (t_sphere *)hit.obj;
		t_vec point = vec_add(ray.origin, vec_mul(ray.direction, hit.t));
		t_vec normal = normalize(vec_sub(point, (t_vec){sphere->coordinate.x, sphere->coordinate.y, sphere->coordinate.z}));
		pixel.r = (sphere->color.r * 0.5f * (normal.i + 1.0f));
		pixel.g = (sphere->color.g * 0.5f * (normal.j + 1.0f));
		pixel.b = (sphere->color.b * 0.5f * (normal.k + 1.0f));
		pixel.a = 255;
	}
	else
	{
		cylinder = (t_cylinder *)hit.obj;
		t_vec point = vec_add(ray.origin, vec_mul(ray.direction, hit.t));
		t_vec normal = normalize(vec_sub(point, (t_vec){cylinder->coordinate.x, cylinder->coordinate.y, cylinder->coordinate.z}));
		pixel.r = (255 * 0.5f * (normal.i + 1.0f));
		pixel.g = (255 * 0.5f * (normal.j + 1.0f));
		pixel.b = (255 * 0.5f * (normal.k + 1.0f));
		pixel.a = 255;
	}
	return (pixel);
} */

t_hit	intersectScene(t_data *data, t_ray ray)
{
	t_hit	hit;
	t_hit	buf_hit;

	hit = nearest_sphere(data, ray);
	buf_hit = nearest_plane(data, ray);
	if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
		hit = buf_hit;
	buf_hit = nearest_cylinder(data, ray);
	if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
		hit = buf_hit;
	hit.position = vec_add(ray.origin, vec_mul(ray.direction, hit.t));
	if (hit.type == 0)
	{
		hit.color = t_color_to_mlx_color(((t_plane *)hit.obj)->color);
		hit.normal = normalize(vec_sub(hit.position, coordinate_to_vec(((t_plane *)hit.obj)->coordinate)));
	}
	else if (hit.type == 1)
	{
		hit.color = t_color_to_mlx_color(((t_sphere *)hit.obj)->color);
		hit.normal = normalize(vec_sub(hit.position, coordinate_to_vec(((t_sphere *)hit.obj)->coordinate)));
	}
	else if (hit.type == 2)
	{
		hit.color = t_color_to_mlx_color(((t_cylinder *)hit.obj)->color);
		hit.normal = normalize(vec_sub(hit.position, coordinate_to_vec(((t_cylinder *)hit.obj)->coordinate)));
	}
	else if (hit.type == 3)
	{
		hit.color = t_color_to_mlx_color(((t_light *)hit.obj)->color);
		hit.normal = normalize(vec_sub(hit.position, coordinate_to_vec(((t_cylinder *)hit.obj)->coordinate)));	
	}
	return (hit);
}

t_vec random_unit_vector()
{
    t_vec v = {
        (float)((drand48() - 0.5) * 2),
        (float)((drand48() - 0.5) * 2),
        (float)((drand48() - 0.5) * 2)
    };
    return normalize(v);
}

t_vec random_in_hemisphere(t_vec normal)
{
    t_vec dir = random_unit_vector();
    return (scalar_product(dir, normal) > 0.0f) ? dir : vec_neg(dir);
}

uint8_t clamp(int x)
{
    if (x > 255) return 255;
    if (x < 0) return 0;
    return x;
}

static uint8_t clamp_float(float value)
{
    if (value < 0.0f) return 0;
    if (value > 255.0f) return 255;
    return (uint8_t)(value + 0.5f);  // arrondi correct
}

mlx_color add_color(mlx_color c1, mlx_color c2)
{
    uint8_t r = clamp(((c1.rgba >> 24) & 0xFF) + ((c2.rgba >> 24) & 0xFF));
    uint8_t g = clamp(((c1.rgba >> 16) & 0xFF) + ((c2.rgba >> 16) & 0xFF));
    uint8_t b = clamp(((c1.rgba >> 8)  & 0xFF) + ((c2.rgba >> 8)  & 0xFF));
    uint8_t a = 255;

    mlx_color result;
    result.rgba = (r << 24) | (g << 16) | (b << 8) | a;
    return result;
}

mlx_color scale_mlx_color(mlx_color color, float factor)
{
    mlx_color result;

    result.r = clamp_float(color.r * factor);
    result.g = clamp_float(color.g * factor);
    result.b = clamp_float(color.b * factor);
    result.a = 255;  // ou color.a si tu veux conserver la transparence
    return result;
}

mlx_color scalar_color(mlx_color c1, mlx_color c2)
{
    uint8_t r = (((c1.rgba >> 24) & 0xFF) * ((c2.rgba >> 24) & 0xFF)) / 255;
    uint8_t g = (((c1.rgba >> 16) & 0xFF) * ((c2.rgba >> 16) & 0xFF)) / 255;
    uint8_t b = (((c1.rgba >> 8)  & 0xFF) * ((c2.rgba >> 8)  & 0xFF)) / 255;
    uint8_t a = 255;

    mlx_color result;
    result.rgba = (r << 24) | (g << 16) | (b << 8) | a;
    return result;
}

mlx_color	shade_pixel(t_data *data, t_ray ray)
{
	int			depth = 0;
	mlx_color	throughput = {.rgba = 0xFFFFFFFF};
	mlx_color	color = {.rgba = 0x000000ff};

	while (depth < data->setting_cam.rbon_nb)
	{
		t_hit	hit = intersectScene(data, ray);
		if (hit.type == -1)
			return (add_color(color, scalar_color((mlx_color){.rgba = 0x000000FF}, throughput)));
		if (hit.type == 3)
		{
			mlx_color localColor = hit.color;
			return (add_color(color, scalar_color(localColor, throughput)));
		}
		mlx_color localColor = hit.color;
		color = add_color(color, scalar_color(localColor, throughput));
		ray.origin = vec_add(hit.position, vec_mul(ray.direction, 0.0001f));
		ray.direction = random_in_hemisphere(hit.normal);
		throughput = scale_mlx_color(throughput, 0.001f);
		depth += 1;
	}
	return (color);
}

mlx_color	render(t_data *data, int x, int y)
{
	t_setting_cam	camera;

	camera = data->setting_cam;
	return (shade_pixel(data, get_antialiasing(data, camera.ray_direction[x][y])));
}
