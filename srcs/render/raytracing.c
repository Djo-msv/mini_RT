#include "miniRT.h"

t_hit	nearest_obj_rt(t_data *data, t_ray ray)
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

t_fcolor	add_light(t_fcolor color, float i)
{
	return ((t_fcolor){color.r + i, color.g + i, color.b + i});
}

t_fcolor	shade_raytracing_pixel(t_data *data, t_ray ray)
{
	t_fcolor	color = {0.0f, 0.0f, 0.0f};
	t_fcolor	l_intensity = {0.0f, 0.0f, 0.0f};

	t_hit hit = nearest_obj_rt(data, ray);
	if (hit.t <= 0)
		return ((t_fcolor){0.0f, 0.0f, 0.0f});
	hit.position = vec_add(ray.origin, vec_mul(ray.direction, hit.t));
//	printf("%d - %d - %d\n", ((t_object *)hit.obj)->color.r, ((t_object *)hit.obj)->color.g, ((t_object *)hit.obj)->color.b);
	color = scalar_color(mlxcolor_to_fcolor(((t_object *)hit.obj)->color), mlxcolor_to_fcolor(((t_light *)(data->scene.light->content))->color));
	if (hit.type == 0)
		hit.normal = normalize(((t_plane *)hit.obj)->normal);
	else if (hit.type == 1)
		hit.normal = normalize(vec_sub(hit.position, ((t_sphere *)hit.obj)->coordinate));
	else
	{
		if (hit.part == 1)
		{
			t_vec	o_c;
			t_vec	projection;
			float	lenght;
			o_c = vec_sub(hit.position, ((t_cylinder *)hit.obj)->coordinate);
			lenght = scalar_product(o_c, ((t_cylinder *)hit.obj)->normal);
			projection = vec_add(((t_cylinder *)hit.obj)->coordinate, vec_mul(((t_cylinder *)hit.obj)->normal, lenght));
			hit.normal = normalize(vec_sub(hit.position, projection));
		}
		else if (hit.part == 2)
			hit.normal = normalize(((t_cylinder *)hit.obj)->normal);
		else
			hit.normal = vec_mul(((t_cylinder *)hit.obj)->normal, -1);
	}
	ray.origin = vec_add(hit.position, vec_mul(hit.normal, 0.0001f));
	ray.direction = normalize(vec_sub(((t_light *)(data->scene.light->content))->coordinate, ray.origin));
	t_hit new_hit = nearest_obj_rt(data, ray);
	if (new_hit.t <= 0.0 || length(vec_sub(((t_light *)(data->scene.light->content))->coordinate, ray.origin)) < new_hit.t)
	{
		float	intensity;
		intensity = scalar_product(hit.normal, ray.direction);
		if (intensity <= 0.0)
			return ((t_fcolor){0.0f, 0.0f, 0.0f});
		l_intensity = add_light(l_intensity, intensity);
	}
	color = scalar_color(l_intensity, color);
	return (color);
}
