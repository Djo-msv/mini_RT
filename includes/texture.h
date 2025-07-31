/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:20:53 by star              #+#    #+#             */
/*   Updated: 2025/07/30 17:53:51 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

typedef struct s_texture
{
	mlx_image	image;
	mlx_image	n_image;
	char		*name;
	char		*n_name;
	int			width;
	int			height;
	int			is_texture;
	int			is_normal;
}				t_texture
__attribute__((aligned(1)));

#endif
