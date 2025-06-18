#ifndef MLX_H
# define MLX_H

typedef struct s_mlx
{
	mlx_context		mlx;
	mlx_window		win;
	mlx_window_create_info	info;
	mlx_image		img;
}	t_mlx
__attribute__((aligned(1)));

int	setup_mlx(t_data *data);

void	  mouse(t_data *data);

void	  run_minirt(t_data *data);

void  key_hook(int key, void* param);
void  window_hook(int event, void* param);
void  mouse_hook(int button, void* param);
void  mouse_wheel_hook(int button, void* param);

#endif
