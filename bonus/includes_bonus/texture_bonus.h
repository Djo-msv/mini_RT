/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:20:53 by star              #+#    #+#             */
/*   Updated: 2025/10/08 14:56:49 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_BONUS_H
# define TEXTURE_BONUS_H

typedef struct s_texture
{
	mlx_image	image;
	mlx_image	n_image;
	char		*name;
	char		*n_name;
	int			width;
	int			height;
	int			n_width;
	int			n_height;
	int			is_texture;
	int			is_normal;
}				t_texture
__attribute__((aligned(1)));

#endif
