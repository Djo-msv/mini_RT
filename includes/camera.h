/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:00:16 by star              #+#    #+#             */
/*   Updated: 2025/07/30 17:00:17 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

void	rotate_camera(t_data *data, float pitch, float yaw);
void	set_camera_window(t_data *data, t_camera *cam);
void	set_camera_ray(t_vec *ray_direction, t_camera *camera, mlx_window_create_info info);

void	move_camera_up(t_data *data, t_camera *cam);
void	move_camera_down(t_data *data, t_camera *cam);
void	move_camera_right(t_data *data, t_camera *cam);
void	move_camera_left(t_data *data, t_camera *cam);
void	move_camera_backward(t_data *data, t_camera *cam);
void	move_camera_forward(t_data *data, t_camera *cam);


#endif
