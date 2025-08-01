/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:38:23 by star              #+#    #+#             */
/*   Updated: 2025/07/31 20:16:25 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"

/*
t_vec2	normal_vec2(int	x, int y, t_camera camera)
{
	float	normal_x;
	float	normal_y;
	t_vec2	result;

	normal_x = ((x * camera.width_coef) - 0.5) * 2;
	normal_y = ((y * camera.height_coef) - 0.5) * 2;
	return (t_vec2){normal_x, normal_y};
}

t_vec3	calcule_ray_direction(t_cam cam, t_vec2 pos)
{
	float	x_ray;
	float	y_ray;

	x_ray = pos.x * tan(cam->rad_foc >> 1) * cam->ratio;
	y_ray = pos.y * tan(cam->rad_foc >> 1);

	return (t_vec3){x_ray, y_ray, 1}
}*/

t_matrix	identity_matrix(t_camera *cam)
{
	t_matrix	t;

	t = (t_matrix){.m = {{cam->right.x, cam->up.x, -cam->forward.x, 0},
	{cam->right.y, cam->up.y, -cam->forward.y, 0},
	{cam->right.z, cam->up.z, -cam->forward.z, 0},
	{0, 0, 0, 1}}};
	return (t);
}

void	rotate_camera(t_camera *cam, float pitch, float yaw, float roll)
{
	t_matrix	x;
	t_matrix	y;
	t_matrix	z;

	if (pitch != 0.0f)
		x = mat4_rotation_x(pitch);
	if (yaw != 0.0f)
		y = mat4_rotation_y(yaw);
	if (roll != 0.0f)
		z = mat4_rotation_z(roll);

	if (yaw != 0.0f)
		cam->cam_rotation = mul_mat4(y, cam->cam_rotation);
	if (pitch != 0.0f)
		cam->cam_rotation = mul_mat4(x, cam->cam_rotation);
	if (roll != 0.0f)
		cam->cam_rotation = mul_mat4(z, cam->cam_rotation);

	cam->right = mul_mat4_to_vec(cam->cam_rotation, cam->right, 1);
	cam->right = normalize(cam->right);
	cam->up = mul_mat4_to_vec(cam->cam_rotation, cam->up, 1);
	cam->up = normalize(cam->up);
	cam->forward = mul_mat4_to_vec(cam->cam_rotation, cam->forward, 1);
	cam->forward = normalize(cam->forward);
}

void	set_camera_window(t_data *data, t_camera *cam)
{
	mlx_window_create_info	info;

	info = data->mlx.info;
	cam->d_height = 2.0f * tan(cam->fov_rad / 2.0f);
	cam->d_width = cam->d_height * ((float)info.width / (float)info.height);
}

void	set_camera_value(t_data *data, t_camera *cam)
{
	t_vec tmp_up = {0.0f, 1.0f, 0.0f};

	cam->forward = normalize(data->scene.camera.orientation);
	if (fabs(cam->forward.y) > 0.999f)
		tmp_up = (t_vec){0.0f, 0.0f, 1.0f};
	cam->right = normalize(cross(tmp_up, cam->forward));
	cam->up = cross(cam->forward, cam->right);
	cam->coordinate = data->scene.camera.coordinate;
	cam->cam_rotation = identity_matrix(cam);
	cam->fov_rad = (data->scene.camera.fov * M_PI) / 180;
	set_camera_window(data, cam);
	set_camera_ray(data->pool->ray_direction, cam, data->mlx.info);
}


t_vec	calcule_ray_direction(t_camera *cam, mlx_window_create_info info, int x, int y)
{
	t_vec	dir;
	float	x_ray;
	float	y_ray;

	x_ray = ((x + 0.5f) / info.width - 0.5f);
	y_ray = ((y + 0.5f) / info.height - 0.5f);
	dir = vec_add(
		vec_add(cam->forward, vec_mul(cam->right, x_ray * cam->d_width)),
		vec_mul(cam->up, y_ray * cam->d_height));
	return (dir);
}

void	set_camera_ray(t_vec *ray_direction, t_camera *camera, mlx_window_create_info info)
{
	int		i;
	int		j;

	i = 0;
	while (i != info.height)
	{
		j = 0;
		while (j != info.width)
		{
			*ray_direction = calcule_ray_direction(camera, info, j, i);
//			if ((i == 0 && j == 0) || (i == info.height - 1 && j == info.width - 1) || (i == 0 && j == info.width - 1) || (i == info.height -1 && j == 0))
//				printf("%f - %f - %f\n", ray_direction->x, ray_direction->y, ray_direction->z);
			ray_direction++;
			j++;
		}
		i++;
	}
}
