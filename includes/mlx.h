#ifndef MLX_H
# define MLX_H

int	setup_mlx(t_data *data);
void	set_camera_value(t_data *data, t_camera *cam);

void	mouse_update(t_data *data);

void	  run_minirt(t_data *data);

void  key_hook_up(int key, void* param);
void  key_hook_down(int key, void* param);
void  window_hook(int event, void* param);
void  mouse_hook(int button, void* param);
void  mouse_wheel_hook(int button, void* param);

void	change_antialiasing_mode(t_data *data);
void	change_mode(t_data *data);
void	change_obj(t_data *d, t_hit select, int key);
void	rotate_obj_x(t_data *d, t_hit select, int is_left);
void	rotate_obj_z(t_data *d, t_hit select, int is_left);
void	rotate_obj_y(t_data *d, t_hit select, int is_left);
void	rotate_move_triangle(t_triangle *tr, t_matrix t, int is_rotate);
void	init_elli_mat(t_ellipsoid *e);
void	resize_obj(t_data *d, t_hit select, int key);

void	update_input(t_data *data);

#endif
