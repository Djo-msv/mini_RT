#include "miniRT.h"

t_hit	cylinder_part(t_cylinder *cy, t_ray ray)
{
	float	t1;
	float	t2;
	float	t3;
	t_hit	hit;

	hit.t = 0;
	hit.obj = cy;
	hit.type = 2;
	hit.part = 0;
	t1 = hit_cylinder(cy, cy->radius, ray);
	t2 = hit_base_cylinder(cy, vec_add(cy->coordinate, vec_mul(cy->normal, cy->height / 2)), ray);
	t3 = hit_base_cylinder(cy, vec_sub(cy->coordinate, vec_mul(cy->normal, cy->height / 2)), ray);
	if (t1 > 0.0f && (t1 < hit.t || hit.t == 0))
	{
		hit.t = t1;
		hit.type = 2;
		hit.part = 1;
	}
	if (t2 > 0.0f && (t2 < hit.t || hit.t == 0))
	{
		hit.t = t2;
		hit.type = 2;
		hit.part = 2;
	}
	if (t3 > 0.0f && (t3 < hit.t || hit.t == 0))
	{
		hit.t = t3;
		hit.type = 2;
		hit.part = 3;
	}
	return (hit);
}

t_hit	nearest_cylinder(t_data *data, t_ray ray)
{
	t_hit		hit;
	t_hit		n;
	t_list		*tmp;
	t_cylinder	*cylinder;
	
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	hit.part = 0;
	tmp = data->scene.cylinder;
	while (tmp)
	{
		cylinder = (t_cylinder *)tmp->content;
		n = cylinder_part(cylinder, ray);
		if (n.t > 0.0f && (n.t < hit.t || hit.t == 0))
		{
			hit.t = n.t;
			hit.obj = cylinder;
			hit.type = 2;
			hit.part = n.part;
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
	hit.part = 0;
	hit = nearest_sphere(data, ray);
	pl = nearest_plane(data, ray);
	if (pl.t > 0.0f && (pl.t < hit.t || hit.t == 0))
		hit = pl;
	cy = nearest_cylinder(data, ray);
	if (cy.t > 0.0f && (cy.t < hit.t || hit.t == 0))
		hit = cy;
	return (hit);
}

int clamp(float v)
{
	if (v < 0)
		return (0);
	if (v > 255)
		return (255);
	return (v);
}

t_color	vec_to_color(t_vec vec)
{
	return ((t_color){clamp(vec.x * 255), clamp(vec.y * 255), clamp(vec.z * 255)});
}

t_vec	color_to_vec(t_color c)
{
	return (create_vec((float)c.r / 255.0, (float)c.g / 255.0, (float)c.b / 255.0));
}

t_vec	mul_color(t_vec c1, t_vec c2)
{
	return (create_vec(c1.x * c2.x, c1.y * c2.y, c1.z * c2.z));
}

t_vec	add_light(t_vec vec, float i)
{
	return (create_vec(vec.x + i, vec.y + i, vec.z + i));
}

mlx_color	ray_color(t_data *data, t_ray ray)
{
	t_vec 		point;
	t_vec 		normal;
	t_vec		l_intensity;
	t_vec		r_color;
	t_ray		light;
	t_hit		hit;
	int			i;

	i = 0;
	l_intensity = create_vec(0 ,0 ,0);
	while (i < 1)
	{
		hit = nearest_obj(data, ray);
		if (hit.t <= 0)
			return ((mlx_color){.rgba = 0x000000FF});
		point = vec_add(ray.origin, vec_mul(ray.direction, hit.t));

		r_color = mul_color(color_to_vec(((t_object *)hit.obj)->color), color_to_vec(((t_light *)(data->scene.light->content))->color));
		if (hit.type == 0)
			normal = normalize(((t_plane *)hit.obj)->normal);
		else if (hit.type == 1)
			normal = normalize(vec_sub(point, ((t_sphere *)hit.obj)->coordinate));
		else
		{
			if (hit.part == 1)
			{
				t_vec	o_c;
				t_vec	projection;
				float	lenght;

				o_c = vec_sub(point, ((t_cylinder *)hit.obj)->coordinate);
				lenght = scalar_product(o_c, ((t_cylinder *)hit.obj)->normal);
				projection = vec_add(((t_cylinder *)hit.obj)->coordinate, vec_mul(((t_cylinder *)hit.obj)->normal, lenght));
				normal = normalize(vec_sub(point, projection));
			}
			else if (hit.part == 2)
				normal = normalize(((t_cylinder *)hit.obj)->normal);
			else
				normal = vec_mul(((t_cylinder *)hit.obj)->normal, -1);
		}
		point = vec_add(point, vec_mul(normal, 0.00001));
		light.origin = point;
		light.direction = normalize(vec_sub(((t_light *)(data->scene.light->content))->coordinate, point));
		hit = nearest_obj(data, light);
		if (hit.t <= 0.0 || length(vec_sub(((t_light *)(data->scene.light->content))->coordinate, light.origin)) < hit.t)
		{
			float	intensity;
			intensity = scalar_product(normal, light.direction);
			if (intensity <= 0.0)
				break ;
			l_intensity = add_light(l_intensity, intensity);
		}
		i++;
	}
	r_color = mul_color(l_intensity, r_color);
	t_color c = vec_to_color(r_color);
	return ((mlx_color){.r = c.r, .g = c.g, .b = c.b, .a = 255});
}

mlx_color	render(t_data *data, int x, int y)
{
	t_setting_cam	camera;

	camera = data->setting_cam;
	return (ray_color(data, get_antialiasing(data, camera.ray_direction[x][y])));
}
