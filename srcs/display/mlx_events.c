#include "miniRT.h"

void	move_camera_forward(t_data *data, t_setting_cam *cam)
{
	t_vec flat = cam->forward;

	flat.j = 0;
	flat = normalize(flat);
	cam->camera_center.i += flat.i * 0.1f;
	cam->camera_center.k += flat.k * 0.1f;
	rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_backward(t_data *data, t_setting_cam *cam)
{
	t_vec flat = cam->forward;

	flat.j = 0;
	flat = normalize(flat);
	cam->camera_center.i -= flat.i * 0.1f;
	cam->camera_center.k -= flat.k * 0.1f;
	rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_left(t_data *data, t_setting_cam *cam)
{
    t_vec up = {0.0f, 1.0f, 0.0f};
	t_vec flat = cam->forward;

	flat.j = 0;
	flat = normalize(flat);
    t_vec left = cross(up, flat);
    
	cam->camera_center.i -= left.i * 0.1f;
    cam->camera_center.k -= left.k * 0.1f;
    rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_right(t_data *data, t_setting_cam *cam)
{
    t_vec up = {0.0f, 1.0f, 0.0f};
	t_vec flat = cam->forward;

	flat.j = 0;
	flat = normalize(flat);
    t_vec right = cross(up, flat);
	cam->camera_center.i += right.i * 0.1f;
    cam->camera_center.k += right.k * 0.1f;
	rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_up(t_data *data, t_setting_cam *cam)
{
	cam->camera_center.j -= 0.1f;
	rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_down(t_data *data, t_setting_cam *cam)
{
	cam->camera_center.j += 0.1f;
	rotate_camera(data, cam->pitch, cam->yaw);
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

void mouse_hook(int button, void* param)
{
	t_data	*data = (t_data *)param;

    printf("-> %d\n", button);
	if (button == 3)
	{
		data->setting_cam.move = !data->setting_cam.move;
		change_mode(data);
	}
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
