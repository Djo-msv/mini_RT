#ifndef CAMERA_H
# define CAMERA_H

typedef struct s_setting_cam
{
	float	ratio;
	int		width;
	int		height;
	float	focal_length;
	float	viewport_height;
	float	viewport_width;
	float	pixel_samples_scale;
	int		rbon_nb;
	float	yaw;
	float	pitch;

	t_vec	camera_center;
	t_vec	viewport_h;
	t_vec	viewport_v;
	t_vec	pixel_delta_h;
	t_vec	pixel_delta_v;
	t_vec	viewport_upper_left;
	t_vec	pixel00_loc;
	t_vec	forward;

	t_vec	**ray_direction;

	float	rand_h;
	float	rand_v;
	float	res_h;
	float	res_v;

	bool	move;

}	t_setting_cam
__attribute__((aligned(1)));

void	move_camera_down(t_data *data, t_setting_cam *cam);
void	move_camera_up(t_data *data, t_setting_cam *cam);
void	move_camera_right(t_data *data, t_setting_cam *cam);
void	move_camera_left(t_data *data, t_setting_cam *cam);
void	move_camera_backward(t_data *data, t_setting_cam *cam);
void	move_camera_forward(t_data *data, t_setting_cam *cam);

void	rotate_camera(t_data *data, float pitch, float yaw);

void	setup_camera_setting(t_data *data);

#endif
