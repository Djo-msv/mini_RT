#include "miniRT.h"

void	move_obj_x(t_data *d, t_hit select, int is_left)
{
	t_matrix		t_x;

	if (!is_left)
		t_x = mat4_translation(0.1, 0.0, 0.0);
	else
		t_x = mat4_translation(-0.1, 0.0, 0.0);
	if (select.type == 0)
		((t_plane *)select.obj)->coordinate = mul_mat4_to_vec(t_x, ((t_plane *)select.obj)->coordinate, 1);
	if (select.type == 1)
		((t_sphere *)select.obj)->coordinate = mul_mat4_to_vec(t_x, ((t_sphere *)select.obj)->coordinate, 1);
	else
		((t_cylinder *)select.obj)->coordinate = mul_mat4_to_vec(t_x, ((t_cylinder *)select.obj)->coordinate, 1);
	d->image.nb_images = 0;
}

void	rotate_obj_x(t_data *d, t_hit select, int is_left)
{
	t_matrix	r_x;

	if (!is_left)
		r_x = mat4_rotation_x(0.1);
	else
		r_x = mat4_rotation_x(-0.1);
	if (select.type == 0)
	{
		((t_plane *)select.obj)->normal = mul_mat4_to_vec(r_x, ((t_plane *)select.obj)->normal, 0);
		((t_plane *)select.obj)->normal = normalize(((t_plane *)select.obj)->normal);
	}
	else if (select.type == 2)
	{
		t_cylinder *c = (t_cylinder *)select.obj;
		c->normal = mul_mat4_to_vec(r_x, c->normal, 0);
		c->normal = normalize(c->normal);
	}
	d->image.nb_images = 0;
}

void	rotate_obj_z(t_data *d, t_hit select, int is_left)
{
	t_matrix	r_z;

	if (!is_left)
		r_z = mat4_rotation_z(0.1);
	else
		r_z = mat4_rotation_z(-0.1);
	if (select.type == 0)
	{
		((t_plane *)select.obj)->normal = mul_mat4_to_vec(r_z, ((t_plane *)select.obj)->normal, 0);
		((t_plane *)select.obj)->normal = normalize(((t_plane *)select.obj)->normal);
	}
	else if (select.type == 2)
	{
		t_cylinder *c = (t_cylinder *)select.obj;
		c->normal = mul_mat4_to_vec(r_z, c->normal, 0);
		c->normal = normalize(c->normal);
	}
	d->image.nb_images = 0;
}

void	rotate_obj_y(t_data *d, t_hit select, int is_left)
{
	t_matrix	r_y;

	if (!is_left)
		r_y = mat4_rotation_y(0.1);
	else
		r_y = mat4_rotation_y(-0.1);
	if (select.type == 0)
	{
		((t_plane *)select.obj)->normal = mul_mat4_to_vec(r_y, ((t_plane *)select.obj)->normal, 0);
		((t_plane *)select.obj)->normal = normalize(((t_plane *)select.obj)->normal);
	}
	else if (select.type == 2)
	{
		t_cylinder *c = (t_cylinder *)select.obj;
		c->normal = mul_mat4_to_vec(r_y, c->normal, 0);
		c->normal = normalize(c->normal);
	}
	d->image.nb_images = 0;
}

void	move_obj_z(t_data *d, t_hit select, int is_forward)
{
	t_matrix		t_z;

	if (!is_forward)
		t_z = mat4_translation(0.0, 0.0, -0.1);
	else
		t_z = mat4_translation(0.0, 0.0, 0.1);
	if (select.type == 0)
		((t_plane *)select.obj)->coordinate = mul_mat4_to_vec(t_z, ((t_plane *)select.obj)->coordinate, 1);
	if (select.type == 1)
		((t_sphere *)select.obj)->coordinate = mul_mat4_to_vec(t_z, ((t_sphere *)select.obj)->coordinate, 1);
	else
		((t_cylinder *)select.obj)->coordinate = mul_mat4_to_vec(t_z, ((t_cylinder *)select.obj)->coordinate, 1);
	d->image.nb_images = 0;
}

void	move_obj_y(t_data *d, t_hit select, int is_up)
{
	t_matrix		t_y;

	if (!is_up)
		t_y = mat4_translation(0.0, -0.1, 0.0);
	else
		t_y = mat4_translation(0.0, 0.1, 0.0);
	if (select.type == 0)
		((t_plane *)select.obj)->coordinate = mul_mat4_to_vec(t_y, ((t_plane *)select.obj)->coordinate, 1);
	if (select.type == 1)
		((t_sphere *)select.obj)->coordinate = mul_mat4_to_vec(t_y, ((t_sphere *)select.obj)->coordinate, 1);
	else
		((t_cylinder *)select.obj)->coordinate = mul_mat4_to_vec(t_y, ((t_cylinder *)select.obj)->coordinate, 1);
	d->image.nb_images = 0;
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
	if (d->scene.select.rotate_mode)
	{
		if (key == 79)
			rotate_obj_x(d, select, 0);
		if (key == 80)
			rotate_obj_x(d, select, 1);
		if (key == 82)
			rotate_obj_y(d, select, 1);
		if (key == 81)
			rotate_obj_y(d, select, 0);
	}
	else
	{
		if (d->scene.select.up_mode)
		{
			if (key == 82)
				move_obj_y(d, select, 1);
			if (key == 81)
				move_obj_y(d, select, 0);
		}
		else
		{
			if (key == 79)
				move_obj_x(d, select, 0);
			if (key == 80)
				move_obj_x(d, select, 1);
			if (key == 82)
				move_obj_z(d, select, 1);
			if (key == 81)
				move_obj_z(d, select, 0);
		}
	}
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
	if (!(((t_data *)param)->scene.select.hit.t <= 0))
		change_obj((t_data *)param, ((t_data *)param)->scene.select.hit, key);
	if (key == 51)
		((t_data *)param)->scene.select.up_mode = !((t_data *)param)->scene.select.up_mode;
	if (key == 21)
		((t_data *)param)->scene.select.rotate_mode = !((t_data *)param)->scene.select.rotate_mode;
	printf("%d\n", key);
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
	d->scene.select.hit = nearest_obj(d, ray);
	if (d->scene.select.hit.t <= 0)
		return ;
	if (d->setting_cam.move)
		destroy_obj(d, d->scene.select.hit);
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
