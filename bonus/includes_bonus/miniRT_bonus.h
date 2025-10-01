/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:00:34 by star              #+#    #+#             */
/*   Updated: 2025/10/01 20:46:29 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdatomic.h>
# include <time.h>

# include "../../lib_RT/includes/lib_rt.h"
# include "../../MacroLibX/includes/mlx.h"
# include "../../MacroLibX/includes/mlx_extended.h"

# include "vector_bonus.h"
# include "matrix_bonus.h"
# include "texture_bonus.h"
# include "object_bonus.h"
# include "setup_bonus.h"
# include "render_bonus.h"
# include "color_bonus.h"
# include "display_bonus.h"
# include "camera_bonus.h"
# include "mlx_bonus.h"
# include "parsing_bonus.h"
# include "ray_tracing_bonus.h"
# include "thread_bonus.h"
# include "alloc_bonus.h"
# include "print_bonus.h"

# define RENDER_DISTANCE 99.9f

#endif
