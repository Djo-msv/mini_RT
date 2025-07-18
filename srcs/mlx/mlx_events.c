/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:06:52 by star              #+#    #+#             */
/*   Updated: 2025/07/15 17:43:06 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	else if (select.type == 3)
		delete_one(&d->scene.light, select.obj);
	else if (select.type == 4)
		delete_one(&d->scene.triangle, select.obj);
	else if (select.type == 0)
		delete_one(&d->scene.plane, select.obj);
	d->image.nb_images = 0;
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
	if (key == 224)
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
	// printf("%d\n", key);
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
		((t_data *)param)->info.y = mlx->info.width;
		((t_data *)param)->info.x = mlx->info.height;
		print_info(&((t_data *)param)->info);
		atomic_fetch_add(((t_data *)param)->generation_id, 1);
		setup_camera_setting((t_data *)param);
		change_thread_setting((t_data *)param);
		atomic_fetch_add(((t_data *)param)->generation_id, 1);
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
		t_vec	pixel_center;
		pixel_center = vec_add(
			vec_add(d->setting_cam.pixel00_loc, vec_mul(d->setting_cam.pixel_delta_h, x)),
			vec_mul(d->setting_cam.pixel_delta_v, y));
		ray = create_ray(d->setting_cam.camera_center, vec_sub(pixel_center, d->setting_cam.camera_center));
	}
	d->scene.select.hit = nearest_obj(d, ray, true);
	if (d->scene.select.hit.t <= 0)
		return ;
	if (d->setting_cam.move)
		destroy_obj(d, d->scene.select.hit);
}


void mouse_hook(int button, void* param)
{
	t_data	*data = (t_data *)param;

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
