/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:00:27 by star              #+#    #+#             */
/*   Updated: 2025/09/25 18:01:07 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_BONUS_H
# define IMAGE_BONUS_H

typedef struct s_image
{
	size_t		nb_images;
	double		coef_new_p;
	double		coef_old_p;
	bool		antialiasing;

	t_fcolor	*buf_img;
	mlx_color	*mlx_img;
}	t_render_image
__attribute__((aligned(1)));

#endif
