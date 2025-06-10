#ifndef DISPLAY_H
# define DISPLAY_H

void 	key_hook(int key, void* param);
void 	window_hook(int event, void* param);
void	mouse_hook(int button, void* param);
void	mouse_wheel_hook(int button, void* param);


void	clear_image(t_mlx *mlx);
void	new_image(t_data *data, t_mlx *mlx);

void	run_minirt(t_data *data);

void	display_screen(t_data *data);

int	setup_mlx(t_data *data);
void	mouse(t_data *data);
void	rotate_camera(t_data *data, float pitch, float yaw);

void	change_antialiasing_mode(t_data *data);
void	change_mode(t_data *data);

#endif
