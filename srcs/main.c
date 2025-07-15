#include "miniRT.h"

void		setup_minirt(t_data *data)
{
	data->generation_id = malloc(sizeof(atomic_uint));
	atomic_init(data->generation_id, 0);
	setup_mlx(data);
	alloc_thread(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(data));
	if (parse(&data, argc, argv))
		return (1);
	setup_minirt(&data);
	data.texture= mlx_new_image_from_file(data.mlx.mlx, "texture/bumb.jpg", 0, 0);
	run_minirt(&data);
	free_data(&data);
	return(0);
}
