#include "miniRT.h"

t_hit	intersectScene(t_data *data, t_ray ray, bool direct_light)
{
	t_hit	hit;

	hit = nearest_obj(data, ray, direct_light);
	if (hit.type == 0)
	{
		if (1)
		{
			int	checker = ((int)floor(hit.position.x / 2) + (int)floor(hit.position.z / 2)) % 2;
			if (checker)
				hit.color = mlxcolor_to_fcolor(((t_plane *)hit.obj)->color);
			else 
				hit.color = (t_fcolor){0.0f, 0.0f, 0.0f};
		}
		else
			hit.color = mlxcolor_to_fcolor(((t_plane *)hit.obj)->color);
		hit.normal = normalize(((t_plane *)hit.obj)->normal);
		hit.material = 0;
	}
	else if (hit.type == 1)
	{
		if (1)
		{
			mlx_color	pixel;
			t_vec		p;
			int			x;
			int			y;
			float		u;
			float		v;

			p = normalize(vec_sub(hit.position, ((t_sphere *)hit.obj)->coordinate));
			u = 0.5 + atan2(p.z, p.x) / (2 * M_PI);
			v = 0.5 - asin(p.y) / M_PI;
			x = u * 6016;
			y = v * 4016;
			mlx_get_image_region(data->mlx.mlx, data->texture, x, y ,1 ,1, &pixel);
			hit.color = mlxcolor_to_fcolor(pixel);
		}
		else
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
		hit.normal = normalize(vec_sub(hit.position, ((t_light *)hit.obj)->coordinate));	
	}
	else if (hit.type == 4)
	{
		hit.color = mlxcolor_to_fcolor(((t_triangle *)hit.obj)->color);
		hit.normal = ((t_triangle *)hit.obj)->normal;
	}
	else if (hit.type == 5)
	{
		t_ellipsoid	*e = (t_ellipsoid *)hit.obj;
		t_vec	hit_local = mul_mat4_to_vec(e->t_inv, hit.position, 1);
		t_vec	normal = normalize(hit_local);
		hit.normal = normalize(mul_mat4_to_vec(e->t_inv_t, normal, 0));
		hit.color = mlxcolor_to_fcolor(e->color);
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
