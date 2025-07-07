#include "miniRT.h"

void	move_camera_forward(t_data *data, t_setting_cam *cam)
{
	t_vec flat = cam->forward;

	flat.y = 0;
	flat = normalize(flat);
	cam->camera_center.x += flat.x * 0.1f;
	cam->camera_center.z += flat.z * 0.1f;
	rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_backward(t_data *data, t_setting_cam *cam)
{
	t_vec flat = cam->forward;

	flat.y = 0;
	flat = normalize(flat);
	cam->camera_center.x -= flat.x * 0.1f;
	cam->camera_center.z -= flat.z * 0.1f;
	rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_left(t_data *data, t_setting_cam *cam)
{
    t_vec up = {0.0f, 1.0f, 0.0f};
	t_vec flat = cam->forward;

	flat.y = 0;
	flat = normalize(flat);
    t_vec left = cross(up, flat);
    
	cam->camera_center.x += left.x * 0.1f;
    cam->camera_center.z += left.z * 0.1f;
    rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_right(t_data *data, t_setting_cam *cam)
{
    t_vec up = {0.0f, 1.0f, 0.0f};
	t_vec flat = cam->forward;

	flat.y = 0;
	flat = normalize(flat);
    t_vec right = cross(up, flat);
	cam->camera_center.x -= right.x * 0.1f;
    cam->camera_center.z -= right.z * 0.1f;
	rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_up(t_data *data, t_setting_cam *cam)
{
	cam->camera_center.y += 0.1f;
	rotate_camera(data, cam->pitch, cam->yaw);
}

void	move_camera_down(t_data *data, t_setting_cam *cam)
{
	cam->camera_center.y -= 0.1f;
	rotate_camera(data, cam->pitch, cam->yaw);
}
