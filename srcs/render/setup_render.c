#include "miniRT.h"

void	create_ray_direction(t_setting_cam *scene)
{
	int		x;
	int		y;
	t_vec	pixel_center;

	scene->ray_direction = ft_calloc((scene->width + 1), sizeof(t_vec *));
	scene->ray_direction[(int)scene->width] = NULL;
	x = 0;
	while (x != scene->width)
	{
		y = 0;
		scene->ray_direction[x] = malloc((scene->height) * sizeof(t_vec));
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

void	setup_camera_setting(t_data *data)
{
	t_setting_cam *scene;

	scene = &data->setting_cam;
	scene->ratio = (float)data->mlx.info.width / data->mlx.info.height;
	scene->width = data->mlx.info.width;
	scene->height = data->mlx.info.height;
	scene->focal_length = 1.0f;
	scene->viewport_height = 2.0f;
	scene->viewport_width = scene->viewport_height * scene->ratio;
	scene->camera_center = create_vec(0, 0, 0);
	scene->viewport_h = create_vec(scene->viewport_width, 0, 0);
	scene->viewport_v = create_vec(0, scene->viewport_height, 0);
	scene->pixel_delta_h = vec_div(scene->viewport_h, scene->width);
	scene->pixel_delta_v = vec_div(scene->viewport_v, scene->height);
	scene->viewport_upper_left = vec_sub(
    vec_sub(
        vec_sub(scene->camera_center, create_vec(0, 0, scene->focal_length)),
        vec_div(scene->viewport_h, 2)),
    	vec_div(scene->viewport_v, 2));
	scene->pixel00_loc = vec_add(scene->viewport_upper_left, vec_mul(vec_add(scene->pixel_delta_h, scene->pixel_delta_v), 0.5f));
//	scene->res_h = length(scene->pixel_delta_h) * data->param.resolution;
//	scene->res_v = length(scene->pixel_delta_v) * data->param.resolution;
	create_ray_direction(scene);
}
