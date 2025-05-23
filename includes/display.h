#ifndef DISPLAY_H
# define DISPLAY_H

# include "miniRT.h"

int		setup_display(t_data *data);
void	key_hook(int key, void* param);
void	window_hook(int event, void* param);

void	clear_image(t_mlx *mlx);
void	new_image(t_data *data, t_mlx *mlx);

void	display_screen(t_data *data);

#endif
