#include "miniRT.h"

void	update_input(t_data *data)
{
	int		tmp = data->info.nb_input;
	t_input	i = data->input;
	(void)data;

	data->info.nb_input = i.z_button + i.s_button + i.a_button + i.d_button +
		i.space_button + i.shift_button + i.deletion_button + i.down_button +
		i.left_button + i.up_button + i.right_button + i.minus_button +
		i.plus_button + i.nine_button + i.zero_button;
	if (data->info.nb_input != tmp)
		print_info(&data->info);
	if (data->pool->restart)
	{
		data->pool->restart = 0;
		data->image.nb_images = 0;
		set_param(data);
		set_camera_window(data, &(data->cam));
		set_camera_ray(data->pool->ray_direction, &(data->cam), data->mlx.info);
	}
		//	mouse_update(data);
//	rotate_camera(0.0f, 0.0f, 0.0f, &(data->cam.forward);
//	printf("%f - %f - %f\n", vec->x, vec->y, vec->z);
}
