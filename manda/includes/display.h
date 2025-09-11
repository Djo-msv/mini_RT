/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:48:29 by star              #+#    #+#             */
/*   Updated: 2025/07/28 15:56:31 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

void	handle_low_resolution(t_data *data, int x, int y, int resolution);
void	display_screen(t_data *data);
void	sampling(t_fcolor *o_pixel, t_fcolor n_pixel,
			double coef_new_p, double coef_old_p);

#endif
