#include "miniRT.h"

void	init_thread(t_data *data)
{
	data->pool = tpool_create(32);
}

void	set_param(t_data *data)
{
	data->param.nb_chunk = ((data->mlx.info.height * data->mlx.info.width) / SIZE_CHUNK) + 1;
}

void	swap_buffer(t_tpool *pool)
{
	t_fcolor	*tmp;

	tpool_wait(pool);
	tmp = pool->buffer_a;
	pool->buffer_a = pool->buffer_b;
	pool->buffer_b = tmp;
}
