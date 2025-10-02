/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:00:49 by star              #+#    #+#             */
/*   Updated: 2025/10/01 19:21:14 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

int	parse(t_data *d, int argc, char **argv);
int	creat_scene(t_data *data, int fd);
int	parse_camera(t_scene *scene, char **args);
int	parse_ambient_light(t_scene *scene, char **args);
int	parse_light(t_scene *scene, char **args);
int	parse_sphere(t_scene *scene, char **args);
int	parse_plane(t_scene *scene, char **args);
int	parse_cylinder(t_scene *scene, char **args);
int	verif_int(char *str, char *max, int l);
int	verfi_float(char *str);
int	verif_fvalue(float min, float max, float value);
int	verif_str(char *str);
int	parse_triangle(t_scene *scene, char **args);
int	parse_ellipsoid(t_scene *scene, char **args);
int	verif_file(char *str);

#endif