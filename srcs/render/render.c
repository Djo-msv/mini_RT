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
		pixel.r = plane->color.r;
		pixel.g = plane->color.g;
		pixel.b = plane->color.b;
		pixel.a = 255;
	}
	else if (hit.type == 1)
	{
		sphere = (t_sphere *)hit.obj;
		t_vec point = vec_add(ray.origin, vec_mul(ray.direction, hit.t));
		t_vec normal = normalize(vec_sub(point, (t_vec){sphere->coordinate.x, sphere->coordinate.y, sphere->coordinate.z}));
		pixel.r = (255 * 0.5f * (normal.i + 1.0f));
		pixel.g = (255 * 0.5f * (normal.j + 1.0f));
		pixel.b = (255 * 0.5f * (normal.k + 1.0f));
		pixel.a = 255;
	}
	else
	{
		cylinder = (t_cylinder *)hit.obj;
		pixel.r = cylinder->color.r;
		pixel.g = cylinder->color.g;
		pixel.b = cylinder->color.b;
		pixel.a = 255;
	}
	return (pixel);	
}

mlx_color	render(t_data *data, int x, int y)
{
	t_setting_cam	camera;

	camera = data->setting_cam;
	return (ray_color(data, get_antialiasing(data, camera.ray_direction[x][y])));
}
