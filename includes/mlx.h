#ifndef MLX_H
# define MLX_H

int	setup_mlx(t_data *data);

void	  mouse(t_data *data);

void	  run_minirt(t_data *data);

void  key_hook(int key, void* param);
void  window_hook(int event, void* param);
void  mouse_hook(int button, void* param);
void  mouse_wheel_hook(int button, void* param);

void	change_antialiasing_mode(t_data *data);
void	change_mode(t_data *data);

#endif
