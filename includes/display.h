#ifndef DISPLAY_H
# define DISPLAY_H

# include "miniRT.h"

typedef struct
{
    mlx_context mlx;
    mlx_window win;
} mlx_t;

int		setup_display(void);
void	key_hook(int key, void* param);
void	window_hook(int event, void* param);

#endif
