#include "miniRT.h"

void	free_data(t_data *data)
{
	free(data->image.new_img);
	free(data->image.old_img);
	free(data->image.mlx_img);
	ft_free_2d_tab((void **)data->setting_cam.ray_direction);
	ft_lstclear(&data->scene.light, free);
	ft_lstclear(&data->scene.cylinder, free);
	ft_lstclear(&data->scene.plane, free);
	ft_lstclear(&data->scene.sphere, free);
	ft_lstclear(&data->scene.ellipsoid, free);
	ft_lstclear(&data->scene.triangle, free);
}
