#include "miniRT.h"

void	mouse(t_data *data)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(data->mlx.mlx, &x, &y);
	printf("%d - %d\n", x, y);
	mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->setting_cam.width >> 1, data->setting_cam.height >> 1);
}
