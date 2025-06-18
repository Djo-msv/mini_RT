#include "miniRT.h"

t_hit	intersectScene(t_data *data, t_ray ray)
{
	t_hit	hit;

	hit = nearest_obj(data, ray);
	if (hit.type == 0)
	{
		hit.color = t_color_to_fcolor(((t_plane *)hit.obj)->color);
		hit.normal = normalize(((t_plane *)hit.obj)->normal);
		hit.material = 1;
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

void	render(t_data *data, t_fcolor *pixel, t_vec ray_direction)
{
//	t_setting_cam	camera;

//	camera = data->setting_cam;
	sampling(pixel, shade_pixel(data, get_antialiasing(data, ray_direction)),
		  data->image.coef_new_p, data->image.coef_old_p);
}
