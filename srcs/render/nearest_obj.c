#include "miniRT.h"

t_hit	nearest_ellipsoid(t_scene scene, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_ellipsoid	*ellipsoid;
	float		t;

	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = scene.ellipsoid;
	while (tmp)
	{
		// printf("alo \n");
		ellipsoid = (t_ellipsoid *)tmp->content;
		t = hit_ellipsoid(ellipsoid, ray);
		if (t > 0.0f && (t < hit.t || hit.t == 0))
		{
			hit.t = t;
			hit.obj = ellipsoid;
			hit.type = 5;
		}
		tmp = tmp->next;
	}
	return (hit);
}

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

t_hit	nearest_cylinder(t_scene scene, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_cylinder	*cylinder;
	float		t;
	
	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = scene.cylinder;
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


t_hit	nearest_plane(t_scene scene, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_plane		*plane;
	float		t;
	
	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = scene.plane;
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

t_hit	nearest_light(t_scene scene, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_light	*light;
	float		t;
	
	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = scene.light;
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

t_hit	nearest_triangle(t_scene scene, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_triangle	*triangle;
	float		t;

	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = scene.triangle;
	while (tmp)
	{
		triangle = (t_triangle *)tmp->content;
		t = hit_triangle(triangle, ray);
		if (t > 0.0f && (t < hit.t || hit.t == 0))
		{
			hit.t = t;
			hit.obj = triangle;
			hit.type = 4;
		}
		tmp = tmp->next;
	}
	return (hit);
}

t_hit	nearest_sphere(t_scene scene, t_ray ray)
{
	t_hit		hit;
	t_list		*tmp;
	t_sphere	*sphere;
	float		t;
	
	t = -1;
	hit.t = 0;
	hit.obj = NULL;
	hit.type = -1;
	tmp = scene.sphere;
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

t_hit	nearest_obj(t_scene scene, t_ray ray, bool direct_light)
{
	t_hit	hit;
	t_hit	buf_hit;

	hit = nearest_sphere(scene, ray);
	buf_hit = nearest_plane(scene, ray);
	hit.material = 0;
	if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
		hit = buf_hit;
//	buf_hit = nearest_cylinder(scene, ray);
//	if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
//		hit = buf_hit;
	buf_hit = nearest_triangle(scene, ray);
	if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
		hit = buf_hit;
	buf_hit = nearest_ellipsoid(scene, ray);
	if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
		hit = buf_hit;
	if (direct_light == false)
	{
		buf_hit = nearest_light(scene, ray);
		if (buf_hit.t > 0.0f && (buf_hit.t < hit.t || hit.t == 0))
			hit = buf_hit;
	}
	hit.position = vec_add(ray.origin, vec_mul(ray.direction, hit.t));
	return (hit);
}

