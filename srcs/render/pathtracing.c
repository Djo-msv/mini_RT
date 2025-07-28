#include "miniRT.h"


t_vec cosine_weighted_hemisphere(t_vec normal)
{
    float r1 = drand48();
    float r2 = drand48();

    float phi = 2.0f * M_PI * r1;
    float r = sqrtf(r2);
    float x = r * cosf(phi);
    float y = r * sinf(phi);
    float z = sqrtf(1.0f - r2);

    t_vec up = (fabsf(normal.z) < 0.999f) ? (t_vec){0, 0, 1} : (t_vec){1, 0, 0};
    t_vec tangent = normalize(cross(up, normal));
    t_vec bitangent = cross(normal, tangent);

    t_vec local = vec_add(
        vec_add(vec_mul(tangent, x), vec_mul(bitangent, y)),
        vec_mul(normal, z)
    );
    return normalize(local);
}

t_vec	reflect(t_vec v, t_vec n)
{
	return vec_sub(v, vec_mul(vec_mul(n, scalar_product(v, n)), 2));
}

void	plastic_light(t_hit	*hit, t_ray *ray, t_fcolor *throughput)
{
	ray->direction = cosine_weighted_hemisphere(hit->normal);
	ray->origin = vec_add(hit->position, vec_mul(ray->direction, 0.0001f));

	float cos_theta = fmaxf(scalar_product(hit->normal, ray->direction), 0.0f);
	*throughput = scalar_color(*throughput, hit->color);
	*throughput = scale_mlx_color(*throughput, cos_theta);
}

void	miror_light(t_hit	*hit, t_ray *ray, t_fcolor *throughput)
{
	ray->direction = reflect(ray->direction, hit->normal);
	ray->origin = vec_add(hit->position, vec_mul(ray->direction, 0.0001f));

	*throughput = scalar_color(*throughput, hit->color);
}

t_fcolor	shade_pathtracing_pixel(t_scene scene, t_ray ray)
{
	int			depth = 0;
	bool		direct_light = true;
	t_fcolor	throughput = {1.0f, 1.0f, 1.0f};
	t_fcolor	color = {0.0f, 0.0f, 0.0f};

	while (depth < 8)
	{
		t_hit	hit = intersectScene(scene, ray, direct_light);
		if (hit.type == -1)
			return (add_color(color, scalar_color((t_fcolor){0.0f, 0.0f, 0.0f}, throughput)));
		if (hit.type == 3)
		{
    		t_fcolor emission = scale_mlx_color(hit.color, 1.0f);
			if (!direct_light)
	    		color = add_color(color, scalar_color(emission, throughput));
			else
				break;
		}
		if (hit.material == 0)
		{
			plastic_light(&hit, &ray, &throughput);
			direct_light = false;
		}
		else if (hit.material == 1)
			miror_light(&hit, &ray, &throughput);
//		else if (hit.material == 2)
//			metal_light();
		depth++;
	}
	return (color);
}
