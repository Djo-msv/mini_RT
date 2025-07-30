/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: star <star@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:00:34 by star              #+#    #+#             */
/*   Updated: 2025/07/30 17:00:35 by star             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdatomic.h>

# include "../lib_RT/includes/lib_rt.h"
# include "../MacroLibX/includes/mlx.h"
# include "../MacroLibX/includes/mlx_extended.h"

# include "vector.h"
# include "matrix.h"
# include "texture.h"
# include "objet.h"
# include "setup.h"
# include "render.h"
# include "color.h"
# include "display.h"
# include "camera.h"
# include "mlx.h"
# include "parsing.h"
# include "ray_tracing.h"
# include "thread.h"
# include "alloc.h"
# include "print.h"

# define MAX_RES_W 3440
# define MAX_RES_H 1440
# define NB_THREAD 8



#endif
