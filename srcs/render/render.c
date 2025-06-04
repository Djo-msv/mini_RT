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

t_vec		color_to_vec(t_color color)
{
	return (t_vec) {(float)color.r / 255.0, (float)color.g / 255.0, (float)color.b / 255.0};
}

t_color		vec_to_color(t_vec color)
{
	return (t_color) {color.i * 255, color.j * 255, color.k * 255};
}

int max(float a, float max)
{
	if (a < max)
		return (max);
	return (a);
}
t_vec reflect(t_vec ray, t_vec normal)
{
	return (vec_sub(ray, vec_mul(vec_mul(normal, scalar_product(ray, normal)), 2.0)));
}

float distance(t_vec a, t_vec b)
{
    float dx = b.i - a.i;
    float dy = b.j - a.j;
    float dz = b.k - a.k;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

t_vec		trace_ray(t_data *data, t_ray ray, float time)
{
	t_vec		light;
	t_vec		color;
	t_hit		hit;

	light = (t_vec) {0., 0., 0.};
	color = (t_vec) {1., 1., 1.};

	int			i = 0;

	while (i < 1)
	{
		hit = nearest_obj(data, ray);
		if (hit.t <= 0)
		{
			// light = vec_add(light, (t_vec) {0.1, 0.3, 0.8});
			break ;
		}

		t_vec normal;
		
		if (hit.type == 0)
		{
			t_plane *plane = (t_plane *)hit.obj;
			color = vec_mul_vec(color, color_to_vec(plane->color));
			normal = normalize(vec_mul(plane->normal, -1.0));
		}
		else if (hit.type == 1)
		{
			t_sphere *sphere = (t_sphere *)hit.obj;
			color = vec_mul_vec(color, color_to_vec(sphere->color));
			t_vec point = vec_add(ray.origin, vec_mul(ray.direction, hit.t));
			normal = normalize(vec_sub(point, (t_vec){sphere->coordinate.x, sphere->coordinate.y, sphere->coordinate.z}));
		}
		else
			return ((t_vec){0., 0., 0.});
		
		t_vec light_pos = (t_vec) {0., -2., -1.};
		(void) time;
		light_pos.i = cos(time) * 2.;
		// light_pos.j = sin(time) * 0.5;

		t_vec point = vec_add(ray.origin, vec_mul(ray.direction, hit.t));
		t_vec light_dir = normalize(vec_sub(light_pos, point));


		//verification lumire visible depuis mon point

		t_ray ray_light;
		ray_light.origin = vec_add(point, vec_mul(normal, 0.01));;
		ray_light.direction = vec_mul(light_dir, 1.0f);

		t_hit new_hit = nearest_obj(data, ray_light);
		if (new_hit.t <= 0.0f || distance(ray_light.origin, light_pos) <= new_hit.t)
		{
			//ici je calcul itnensite lumiere dot product produti calraire blabla
	
			float intensity = scalar_product(normal, light_dir);
			if (intensity <= 0.0f)
				break ;
			
			light = vec_add_uniq(light, intensity);
		}
		

		ray.origin = vec_add(point, vec_mul(normal, 0.01));
		ray.direction = normalize(reflect(ray.direction, normal));

		i++;
	}

	return (vec_mul_vec(color, light));
}

mlx_color	ray_color(t_data *data, t_ray ray, float time)
{
	t_color color;

	color = vec_to_color(trace_ray(data, ray, time));
	
	return (mlx_color) {.r = color.r, .g = color.g, .b = color.b, .a = 255.0};
}

mlx_color	render(t_data *data, int x, int y, float time)
{
	t_setting_cam	camera;

	camera = data->setting_cam;
	return (ray_color(data, get_antialiasing(data, camera.ray_direction[x][y]), time));
}
