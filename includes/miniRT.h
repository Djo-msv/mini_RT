/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:46:26 by nrolland          #+#    #+#             */
/*   Updated: 2025/05/16 19:53:53 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "lib_RT/includes/lib_rt.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include "MacroLibX/includes/mlx.h"

typedef struct s_a_light
{
	float		range;
	int			r;
	int			g;
	int			b;
}				t_a_light;

typedef struct s_cam
{
	int			x;
	int			y;
	int			z;
	int			orient_x;
	int			orient_y;
	int			orient_z;
	int			fov;
}				t_cam;

typedef struct s_light
{
	int			x;
	int			y;
	int			z;
	int			bright;
	//add (unused in mandatory part) R, G, B colors in the range..
}				t_light;

typedef struct s_sphere
{
	int			x;
	int			y;
	int			z;
	int			d;
	int			r;
	int			g;
	int			b;
}				t_sphere;

typedef struct s_plane
{
	int			x;
	int			y;
	int			z;
	int			normal_x;
	int			normal_y;
	int			normal_z;
	int			r;
	int			g;
	int			b;
}				t_plane;

typedef struct s_cylind
{
	int			x;
	int			y;
	int			z;
	int			normal_x;
	int			normal_y;
	int			normal_z;
	int			d;
	int			height;
}				t_cylind;

typedef struct s_data
{
	int		 mouffette;
}				t_data;

int	parse(t_data *d, int argc, char **argv);

#endif