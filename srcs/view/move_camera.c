#include "miniRT"

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
