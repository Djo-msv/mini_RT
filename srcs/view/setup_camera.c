#include "miniRT.h"

void	calculate_ray_direction(t_setting_cam *scene)
{
	int		x;
	int		y;
	t_vec	pixel_center;

	x = 0;
	while (x != scene->width)
	{
		y = 0;
		while (y != scene->height)
		{
			pixel_center = vec_add(
    			vec_add(scene->pixel00_loc, vec_mul(scene->pixel_delta_h, x)),
    			vec_mul(scene->pixel_delta_v, y));
			scene->ray_direction[x][y] = vec_sub(pixel_center, scene->camera_center);
			y++;
		}
		x++;
	}
}

void	alloc_ray_direction(t_setting_cam *scene)
{
	int		x;

	x = 0;
	scene->ray_direction = ft_calloc((MAX_RES_H + 1), sizeof(t_vec *));
	scene->ray_direction[(int)scene->width] = NULL;
	while (x != scene->width)
	{
		scene->ray_direction[x] = malloc(MAX_RES_V * sizeof(t_vec));
		x++;
	}
}

void	calcule_res(t_data *data, t_setting_cam *cam)
{
	t_vec viewport_center = vec_add(
		cam->camera_center,
		vec_scale(cam->forward, cam->focal_length));

	t_vec half_h = vec_scale(cam->viewport_h, 0.5);
	t_vec half_v = vec_scale(cam->viewport_v, 0.5);

	cam->viewport_upper_left = vec_sub(
	    vec_sub(viewport_center, half_h),
	    half_v);

	cam->pixel_delta_h = vec_scale(cam->viewport_h, 1.0f / cam->width);
	cam->pixel_delta_v = vec_scale(cam->viewport_v, 1.0f / cam->height);

	t_vec half_delta_h = vec_scale(cam->pixel_delta_h, 0.5f);
	t_vec half_delta_v = vec_scale(cam->pixel_delta_v, 0.5f);

	cam->pixel00_loc = vec_add(
		vec_add(cam->viewport_upper_left, half_delta_h),
		half_delta_v);
	cam->res_h = length(cam->pixel_delta_h) * data->image.resolution;
	cam->res_v = length(cam->pixel_delta_v) * data->image.resolution;
}

void	calcule_scene(t_data *data, t_setting_cam *scene)
{
	scene->ratio = (float)data->mlx.info.width / data->mlx.info.height;
	scene->width = data->mlx.info.width;
	scene->height = data->mlx.info.height;
	scene->focal_length = 1.0f;
	scene->viewport_height = 2.0f;
	scene->viewport_width = scene->viewport_height * scene->ratio;
}

void	setup_camera_setting(t_data *data)
{
	t_setting_cam *scene;

	scene = &data->setting_cam;
	calcule_scene(data, scene);
	angle_camera(data, scene->pitch, scene->yaw);
	calcule_res(data, scene);
	alloc_ray_direction(scene);
	calculate_ray_direction(scene);
}
