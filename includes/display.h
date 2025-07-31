/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:00:24 by star              #+#    #+#             */
/*   Updated: 2025/07/30 17:00:25 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

void	handle_low_resolution(t_data *data, int x, int y, int resolution);
void	display_screen(t_data *data);
void	sampling(t_data *data);

#endif
