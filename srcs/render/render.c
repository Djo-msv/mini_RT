#include "miniRT.h"

t_hit	intersectScene(t_data *data, t_ray ray, bool direct_light)
{
	t_hit	hit;

	hit = nearest_obj(data, ray, direct_light);
	if (hit.type == 0)
	{
		hit.color = mlxcolor_to_fcolor(((t_plane *)hit.obj)->color);
		hit.normal = normalize(((t_plane *)hit.obj)->normal);
		hit.material = 1;
	}
	else if (hit.type == 1)
	{
		hit.color = mlxcolor_to_fcolor(((t_sphere *)hit.obj)->color);
		hit.normal = normalize(vec_sub(hit.position, ((t_sphere *)hit.obj)->coordinate));
	}
	else if (hit.type == 2)
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
	else if (hit.type == 3)
	{
		hit.color = mlxcolor_to_fcolor(((t_light *)hit.obj)->color);
		hit.normal = normalize(vec_sub(hit.position, ((t_cylinder *)hit.obj)->coordinate));	
	}
	return (hit);
}

void	render(t_data *data, t_fcolor *pixel, t_vec ray_direction)
{
//	t_setting_cam	camera;

//	camera = data->setting_cam;
//	return ;
	*pixel = shade_pathtracing_pixel(data, get_antialiasing(data, ray_direction));
}
