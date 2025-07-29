/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:20:53 by star              #+#    #+#             */
/*   Updated: 2025/07/29 16:26:50 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

typedef struct s_texture
{
	mlx_image	image;
	char		*name;
	int			width;
	int			height;
	int			is_texture;
}				t_texture
__attribute__((aligned(1)));

#endif
