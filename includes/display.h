#ifndef DISPLAY_H
# define DISPLAY_H

void 	key_hook(int key, void* param);
void 	window_hook(int event, void* param);

void	clear_image(t_mlx *mlx);
void	new_image(t_data *data, t_mlx *mlx);

void	run_minirt(t_data *data);

void	display_screen(t_data *data);

int	setup_mlx(t_data *data);


#endif
