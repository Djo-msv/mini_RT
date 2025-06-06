#include "miniRT.h"

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
	// t_hit	sp;
	t_hit	pl;
	t_hit	cy;

	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	hit = nearest_sphere(data, ray);
	pl = nearest_plane(data, ray);
	if (pl.t > 0.0f && (pl.t < hit.t || hit.t == 0))
		hit = pl;
	cy = nearest_cylinder(data, ray);
	if (cy.t > 0.0f && (cy.t < hit.t || hit.t == 0))
		hit = cy;
	return (hit);
}

t_color	vec_to_color(t_vec vec)
{
	return ((t_color){vec.x * 255, vec.y * 255, vec.z * 255});
}

t_vec	color_to_vec(t_color c)
{
	return (create_vec(c.r / 255, c.g / 255, c.b / 255));
}

t_vec	mul_color(t_vec c1, t_vec c2)
{
	return (create_vec(c1.x * c2.x, c1.y * c2.y, c1.z * c2.z));
}

mlx_color	ray_color(t_data *data, t_ray ray)
{
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_hit		hit;
	t_vec 		point;
	t_vec 		normal;
	t_ray		light;
	t_vec		color;

	hit = nearest_obj(data, ray);
	if (hit.t <= 0)
		return ((mlx_color){.rgba = 0x000000FF});
	point = vec_add(ray.origin, vec_mul(ray.direction, hit.t));
	color = mul_color(color_to_vec(((t_object *)hit.obj)->color), color_to_vec(((t_light *)(data->scene.light->content))->color));
	if (hit.type == 0)
		normal = normalize(vec_sub(point, ((t_plane *)plane)->coordinate));
	else if (hit.type == 1)
		normal = normalize(vec_sub(point, ((t_sphere *)sphere)->coordinate));
	else
		normal = normalize(vec_sub(point, ((t_cylinder *)cylinder)->coordinate));
	light.origin = vec_add(point, vec_mul(point, 0.01));
	light.direction = normalize(vec_sub(((t_light *)(data->scene.light->content))->coordinate, point));
	hit = nearest_obj(data, light);
	if (hit.t <= 0)
	{
		float	intensity;
		intensity = scalar_product(normal, light.direction);
		if (intensity <= 0.0)
			return ((mlx_color){color, .a = 255});

	}
	return ();	
}

mlx_color	render(t_data *data, int x, int y)
{
	t_setting_cam	camera;

	camera = data->setting_cam;
	return (ray_color(data, get_antialiasing(data, camera.ray_direction[x][y])));
}
