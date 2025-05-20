#ifndef DISPLAY_H
# define DISPLAY_H

# include "miniRT.h"

int		setup_display(t_data *data);
void	key_hook(int key, void* param);
void	window_hook(int event, void* param);

int	draw_background(t_mlx *mlx);

#endif
