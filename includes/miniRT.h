#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>

# include "../lib_RT/includes/lib_rt.h"
# include "../MacroLibX/includes/mlx.h"
# include "../MacroLibX/includes/mlx_extended.h"

# include "vector.h"
# include "matrix.h"
# include "objet.h"
# include "setup.h"
# include "render.h"
# include "color.h"
# include "display.h"
# include "camera.h"
# include "mlx.h"
# include "parsing.h"
# include "alloc.h"

# define MAX_RES_H 1920
# define MAX_RES_V 1080

t_hit	nearest_cylinder(t_data *data, t_ray ray);
t_hit	nearest_sphere(t_data *data, t_ray ray);
t_hit	nearest_plane(t_data *data, t_ray ray);

#endif
