#include "miniRT.h"

void	free_data(t_data *data)
{
	free(data->image.new_img);
	free(data->image.old_img);
	ft_free_2d_tab((void **)data->setting_cam.ray_direction);
}
