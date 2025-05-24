#ifndef DISPLAY_H
# define DISPLAY_H

# include "miniRT.h"

int		setup_display(t_data *data);
void	key_hook(int key, void* param);
void	window_hook(int event, void* param);

void	setup_scene(t_data *data, t_setting_cam *scene);

void	clear_image(t_mlx *mlx);
void	new_image(t_data *data, t_mlx *mlx);

mlx_color	render(t_data *data, int x, int j);


void	display_screen(t_data *data);

#endif
