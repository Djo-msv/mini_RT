#include "miniRT.h"

void	mouse(t_data *data)
{
	int	x;
	int	y;
	static float	pitch = 0;
	static float	yaw = 0;

	t_setting_cam cam = data->setting_cam;
	mlx_mouse_get_pos(data->mlx.mlx, &x, &y);
	if (data->setting_cam.move)
	{
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, cam.width >> 1, cam.height >> 1);
		if (x - (cam.width >> 1) == 0 && y - (cam.height >> 1) == 0)
			return ;
		yaw -= (x - (float)(cam.width >> 1)) * 0.001f;
		pitch -= (y - (float)(cam.height >> 1)) * 0.001f;
		angle_camera(data, pitch, yaw);
	}
}


