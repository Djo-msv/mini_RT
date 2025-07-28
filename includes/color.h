/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:48:26 by star              #+#    #+#             */
/*   Updated: 2025/07/28 15:53:18 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

void		fcolor_to_mlxcolor(t_data *d, t_fcolor *s,
				mlx_color *dst, size_t n);
t_fcolor	scalar_color(t_fcolor c1, t_fcolor c2);
t_fcolor	scale_mlx_color(t_fcolor color, float factor);
t_fcolor	add_color(t_fcolor c1, t_fcolor c2);
t_fcolor	mlxcolor_to_fcolor(mlx_color color);

#endif
