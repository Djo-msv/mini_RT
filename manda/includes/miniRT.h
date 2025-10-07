/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:48:37 by star              #+#    #+#             */
/*   Updated: 2025/09/30 19:26:16 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>

# include "../../lib_RT/includes/lib_rt.h"
# include "../../MacroLibX/includes/mlx.h"
# include "../../MacroLibX/includes/mlx_extended.h"

# include "vector.h"
# include "matrix.h"
# include "object.h"
# include "setup.h"
# include "render.h"
# include "color.h"
# include "display.h"
# include "camera.h"
# include "mlx.h"
# include "parsing.h"
# include "alloc.h"

# define RENDER_DISTANCE 99.9f

t_hit	nearest_cylinder(t_data *data, t_ray ray);
t_hit	nearest_sphere(t_data *data, t_ray ray);
t_hit	nearest_plane(t_data *data, t_ray ray);

#endif
