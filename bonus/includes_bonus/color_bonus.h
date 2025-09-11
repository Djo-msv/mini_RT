/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:00:19 by star              #+#    #+#             */
/*   Updated: 2025/09/11 17:22:03 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_BONUS_H
# define COLOR_BONUS_H

# define P_NOC_PROMPT "\001\033[0m\002"
# define P_TEAL_BOLD_PROMPT "\001\033[1;36m\002"
# define P_TEAL_LIGHT_PROMPT "\001\033[0;36m\002"
# define P_GREEN_PROMPT "\001\033[0;32m\002"
# define P_PINK_PROMPT "\001\033[0;35m\002"
# define P_BLACK_PROMPT "\001\033[0;30m\002"
# define P_RED_PROMPT "\001\033[0;31m\002"
# define P_NOC "\033[0m"
# define P_BOLD "\033[1m"
# define P_BLACK "\033[0;30m"
# define P_RED "\033[0;31m"
# define P_GREEN "\033[0;32m"
# define P_YELLOW "\033[0;33m"
# define P_BLUE "\033[0;34m"
# define P_PINK "\033[0;35m"
# define P_TEAL "\033[0;36m"

void		fcolor_to_mlxcolor(t_data *data, mlx_color *dst);
t_fcolor	scalar_color(t_fcolor c1, t_fcolor c2);
t_fcolor	scale_mlx_color(t_fcolor color, float factor);
t_fcolor	add_color(t_fcolor c1, t_fcolor c2);
t_fcolor	mlxcolor_to_fcolor(mlx_color color);

#endif
