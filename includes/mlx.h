/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:00:40 by star              #+#    #+#             */
/*   Updated: 2025/07/31 19:13:58 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	change_obj(t_data *d, t_hit select);
void	rotate_obj_x(t_hit select, int is_left);
void	rotate_obj_z(t_hit select, int is_left);
void	rotate_obj_y(t_hit select, int is_left);
void	rotate_move_triangle(t_triangle *tr, t_matrix t, int is_rotate);
void	init_elli_mat(t_ellipsoid *e);
void	resize_obj(t_data *d, t_hit select);
void	move_obj_x(t_hit select, int is_left);
void	move_obj_z(t_hit select, int is_forward);
void	move_obj_y(t_hit select, int is_up);

void	update_input(t_data *data);

#endif
