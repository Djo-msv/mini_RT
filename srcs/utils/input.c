#include "miniRT.h"

void	update_input(t_data *data)
{
	int		tmp = data->info.nb_input;
	t_input	input = data->input;
	(void)data;

	data->info.nb_input = input.z_button + input.s_button + input.a_button + input.d_button + input.space_button + input.shift_button;
	if (data->info.nb_input != tmp)
		print_info(&data->info);
//	mouse_update(data);
//	rotate_camera(0.0f, 0.0f, 0.0f, &(data->cam.forward);
//	printf("%f - %f - %f\n", vec->x, vec->y, vec->z);
}
