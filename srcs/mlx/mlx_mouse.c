#include "miniRT.h"

void	mouse(t_data *data)
{
	int	x;
	int	y;
	static float	pitch = 0;
	static float	yaw = 0;

	t_setting_cam *cam = &data->setting_cam;
	mlx_mouse_get_pos(data->mlx.mlx, &x, &y);
	if (data->setting_cam.move)
	{
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.info.width >> 1, data->mlx.info.height >> 1);
		if (x - (data->mlx.info.width >> 1) == 0 && y - (data->mlx.info.height >> 1) == 0)
			return ;
		yaw -= (x - (float)(cam->width >> 1)) * 0.001f;
		pitch += (y - (float)(cam->height >> 1)) * 0.001f;
		if (pitch > 1.5708f)
			pitch = 1.5707f;
		if (pitch < -1.5708f)
			pitch = -1.5707f;
		cam->yaw = yaw;
		cam->pitch = pitch;
		atomic_fetch_add(data->generation_id, 1);
		rotate_camera(data, pitch, yaw);
		atomic_fetch_add(data->generation_id, 1);
	}
}

