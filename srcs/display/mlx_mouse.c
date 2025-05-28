#include "miniRT.h"



void	mouse(t_data *data)
{
	int	x;
	int	y;

	t_setting_cam cam = data->setting_cam;
	mlx_mouse_get_pos(data->mlx.mlx, &x, &y);
	printf("%d - %d\n", x, y);
//	int dx = x - (cam.width >> 1);
//	int dy = y - (cam.height >> 1);
	mlx_mouse_move(data->mlx.mlx, data->mlx.win, cam.width >> 1, cam.height >> 1);
//	rotate_camera(&cam, dx, dy);
}


