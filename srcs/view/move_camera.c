#include "miniRT.h"

void	move_camera_forward(t_data *data, t_camera *cam)
{
	t_vec	flat;

	flat = cam->forward;
	if (fabs(cam->forward.y) > 0.999f)
		flat = cam->up;
	flat.y = 0;
	flat = normalize(flat);
	cam->coordinate.x += flat.x * 0.05f;
	cam->coordinate.z += flat.z * 0.05f;
//	rotate_camera(data, cam->pitch, cam->yaw);
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;

}

void	move_camera_backward(t_data *data, t_camera *cam)
{
	t_vec	flat;

	flat = cam->forward;
	if (fabs(cam->forward.y) > 0.999f)
		flat = cam->up;
	flat.y = 0;
	flat = normalize(flat);
	cam->coordinate.x -= flat.x * 0.05f;
	cam->coordinate.z -= flat.z * 0.05f;
//	rotate_camera(data, cam->pitch, cam->yaw);
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;
}

void	move_camera_left(t_data *data, t_camera *cam)
{
	t_vec	up;
	t_vec	flat;
	t_vec	left;

	up = (t_vec){0.0f, 1.0f, 0.0f};
	flat = cam->forward;
	if (fabs(cam->forward.y) >= 1.0f)
		flat = cam->up;
	flat.y = 0;
	flat = normalize(flat);
	left = cross(up, flat);
	cam->coordinate.x -= left.x * 0.05f;
	cam->coordinate.z -= left.z * 0.05f;
//	rotate_camera(data, cam->pitch, cam->yaw);
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;

}

void	move_camera_right(t_data *data, t_camera *cam)
{
	t_vec	up;
	t_vec	flat;
	t_vec	right;

	up = (t_vec){0.0f, 1.0f, 0.0f};
	flat = cam->forward;
	if (fabs(cam->forward.y) > 0.999f)
		flat = cam->up;
	flat.y = 0;
	flat = normalize(flat);
	right = cross(up, flat);
	cam->coordinate.x += right.x * 0.05f;
	cam->coordinate.z += right.z * 0.05f;
//	rotate_camera(data, cam->pitch, cam->yaw);
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;
}

void	move_camera_up(t_data *data, t_camera *cam)
{
	cam->coordinate.y += 0.05f;
//	rotate_camera(data, cam->pitch, cam->yaw);
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;
}

void	move_camera_down(t_data *data, t_camera *cam)
{
	cam->coordinate.y -= 0.05f;
//	rotate_camera(data, cam->pitch, cam->yaw);
	data->scene.camera.coordinate = cam->coordinate;
	data->image.nb_images = 0;

}
