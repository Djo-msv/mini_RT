#include "miniRT.h"

t_fcolor t_color_to_fcolor(t_color color)
{
	t_fcolor fcolor;

	fcolor.r = color.r / 255.0f;
	fcolor.g = color.g / 255.0f;
	fcolor.b = color.b / 255.0f;

	return fcolor;
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
		t = hit_sphere(light->coordinate, 3.0f, ray);
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
	buf_hit = nearest_light(data, ray);
	if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
		hit = buf_hit;
	hit.position = vec_add(ray.origin, vec_mul(ray.direction, hit.t));
	if (hit.type == 0)
	{
		hit.color = t_color_to_fcolor(((t_plane *)hit.obj)->color);
		hit.normal = normalize(((t_plane *)hit.obj)->normal);
	}
	else if (hit.type == 1)
	{
		hit.color = t_color_to_fcolor(((t_sphere *)hit.obj)->color);
		hit.normal = normalize(vec_sub(hit.position, coordinate_to_vec(((t_sphere *)hit.obj)->coordinate)));
	}
	else if (hit.type == 2)
	{
		hit.color = t_color_to_fcolor(((t_cylinder *)hit.obj)->color);
		hit.normal = normalize(vec_sub(hit.position, coordinate_to_vec(((t_cylinder *)hit.obj)->coordinate)));
	}
	else if (hit.type == 3)
	{
		hit.color = t_color_to_fcolor(((t_light *)hit.obj)->color);
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

t_fcolor	shade_pixel(t_data *data, t_ray ray)
{
	int			depth = 0;
	t_fcolor	throughput = {1.0f, 1.0f, 1.0f};
	t_fcolor	color = {0.0f, 0.0f, 0.0f};

	while (depth < data->setting_cam.rbon_nb)
	{
		t_hit	hit = intersectScene(data, ray);
		if (hit.type == -1)
			return (add_color(color, scalar_color((t_fcolor){0.0f, 0.0f, 0.0f}, throughput)));
		if (hit.type == 3)
		{
    		t_fcolor emission = scale_mlx_color(hit.color, 100.0f);
    		return scalar_color(emission, throughput);
		}
		ray.origin = vec_add(hit.position, vec_mul(ray.direction, 0.0001f));
		ray.direction = random_in_hemisphere(hit.normal);
		float cos_theta = fmaxf(vec_dot(hit.normal, ray.direction), 0.0f);
		throughput = scalar_color(throughput, hit.color);
		throughput = scale_mlx_color(throughput, cos_theta);
		depth += 1;
	}
	return (color);
}

t_fcolor	render(t_data *data, int x, int y)
{
	t_setting_cam	camera;

	camera = data->setting_cam;
	return (shade_pixel(data, get_antialiasing(data, camera.ray_direction[x][y])));
}
