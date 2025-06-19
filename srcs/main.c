#include "miniRT.h"

void		setup_minirt(t_data *data)
{
	setup_mlx(data);
	alloc_thread(data);
	if (!data->thread)
		printf("caca\n");
	setup_camera_setting(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(data));
	if (parse(&data, argc, argv))
		return (1);
	setup_minirt(&data);
	run_minirt(&data);
	free_data(&data);
	return(0);
}
