#include "miniRT.h"

void	move_camera_forward(t_data *data, t_setting_cam *cam)
{
	t_vec flat = cam->forward;

	flat.y = 0;
	flat = normalize(flat);
	cam->camera_center.x += flat.x * 0.1f;
	cam->camera_center.z += flat.z * 0.1f;
	angle_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_backward(t_data *data, t_setting_cam *cam)
{
	t_vec flat = cam->forward;

	flat.y = 0;
	flat = normalize(flat);
	cam->camera_center.x -= flat.x * 0.1f;
	cam->camera_center.z -= flat.z * 0.1f;
	angle_camera(data, cam->pitch, cam->yaw);
	(void)data;
}

void	move_camera_left(t_data *data, t_setting_cam *cam)
{
    t_vec up = {0.0f, 1.0f, 0.0f};
	t_vec flat = cam->forward;

	flat.y = 0;
	flat = normalize(flat);
    t_vec left = cross(up, flat);
    
	cam->camera_center.x -= left.x * 0.1f;
    cam->camera_center.z -= left.z * 0.1f;
    angle_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_right(t_data *data, t_setting_cam *cam)
{
    t_vec up = {0.0f, 1.0f, 0.0f};
	t_vec flat = cam->forward;

	flat.y = 0;
	flat = normalize(flat);
    t_vec right = cross(up, flat);
	cam->camera_center.x += right.x * 0.1f;
    cam->camera_center.z += right.z * 0.1f;
    angle_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_up(t_data *data, t_setting_cam *cam)
{
	cam->camera_center.y -= 0.1f;
	angle_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_down(t_data *data, t_setting_cam *cam)
{
	cam->camera_center.y += 0.1f;
	angle_camera(data, cam->pitch, cam->yaw);
}

void	delete_one(t_list **list, void *obj)
{
	t_list	*lst;
	t_list	*prev;

	prev = NULL;
	lst = *list;
	while (lst)
	{
		if (lst->content == obj)
		{
			if (prev)
				prev->next = lst->next;
			else
				*list = lst->next;
			ft_lstdelone(lst, free);
			return ;
		}
		prev = lst;
		lst = lst->next;
	}
}

void	destroy_obj(t_data *d, t_hit select)
{
	if (select.type == 1)
		delete_one(&d->scene.sphere, select.obj);
	else if (select.type == 2)
		delete_one(&d->scene.cylinder, select.obj);
	else
		delete_one(&d->scene.plane, select.obj);
	d->image.nb_images = 0;
}

void	change_obj(t_data *d, t_hit select, int key)
{
	if (key == 79)
	if (key == 80)
	if (key == 82)
	if (key == 41)
	if (select.type == 1)
	{
		delete_one(&d->scene.sphere, select.obj);
	}
	if (select.type == 2)
		delete_one(&d->scene.cylinder, select.obj);
	// ((t_cylinder *)hit.obj)->normal = vec_add(((t_cylinder *)hit.obj)->normal, create_vec(0.0, 0.0, 0.1));

}

void key_hook(int key, void* param)
{
	static bool	fullscreen = false;
	t_mlx 		*mlx;

	mlx = &((t_data *)param)->mlx;
    if(key == 41)
		mlx_loop_end(mlx->mlx);
	if (key == 26 || key == 4 || key == 22 || key == 7)
		((t_data *)param)->image.nb_images = 0;
	if (key == 26)
		move_camera_forward((t_data *)param, &((t_data *)param)->setting_cam);
	if (key == 22)
		move_camera_backward((t_data *)param, &((t_data *)param)->setting_cam);
	if (key == 7)
		move_camera_left((t_data *)param, &((t_data *)param)->setting_cam);
	if (key == 4)
		move_camera_right((t_data *)param, &((t_data *)param)->setting_cam);
	if (key == 44)
		move_camera_up((t_data *)param, &((t_data *)param)->setting_cam);
	if (key == 225)
		move_camera_down((t_data *)param, &((t_data *)param)->setting_cam);
	if (key == 68)
	{
		fullscreen = !fullscreen;
		mlx_set_window_fullscreen(mlx->mlx, mlx->win , fullscreen);
	}
	if (key == 43)
		change_antialiasing_mode((t_data *)param);
	if (!(((t_data *)param)->scene.select.t <= 0))
		change_obj((t_data *)param, ((t_data *)param)->scene.select, key);
	printf("->%d\n", key);
}

void window_hook(int event, void* param)
{
	t_mlx *mlx;

	mlx = &((t_data *)param)->mlx;
	if(event == 0)
		mlx_loop_end(mlx->mlx);
	if (event == 8)
	{
		mlx_get_window_size(mlx->mlx, mlx->win, &mlx->info.width, &mlx->info.height);
		new_image((t_data *)param, mlx);
		ft_free_2d_tab((void **)((t_data *)param)->setting_cam.ray_direction);
		setup_camera_setting((t_data *)param);
	}
}

void	handle_select_obj(t_data *d)
{
	t_ray	ray;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (d->setting_cam.move)
		ray = create_ray(d->setting_cam.camera_center, d->setting_cam.forward);
	else
	{
		mlx_mouse_get_pos(d->mlx.mlx, &x, &y);
		ray = create_ray(d->setting_cam.camera_center, d->setting_cam.ray_direction[x][y]);
	}
	d->scene.select = nearest_obj(d, ray);
	if (d->scene.select.t <= 0)
		return ;
	if (d->setting_cam.move)
		destroy_obj(d, d->scene.select);
}

void mouse_hook(int button, void* param)
{
	t_data	*data = (t_data *)param;

    printf("-> %d\n", button);
	if (button == 3)
	{
		data->setting_cam.move = !data->setting_cam.move;
		change_mode(data);
	}
	if (button == 1)
		handle_select_obj(data);
}

void mouse_wheel_hook(int button, void* param)
{
	t_data *data = (t_data *)param;

	if (button == 2)
		data->image.resolution++;
	if (button == 1 && data->image.resolution > 1)
		data->image.resolution--;
	else if (data->image.resolution == 1)
		return ;
	if (button == 1 || button == 2)
	{
		data->image.nb_images = 0;
		calcule_res(data, &data->setting_cam);
	}
}
