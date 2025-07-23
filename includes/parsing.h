#ifndef PARSING_H
# define PARSING_H

int     parse(t_data *d, int argc, char **argv);
int     creat_scene(t_data *data, int fd);
int     parse_camera(t_scene *scene, char **args);
int     parse_ambient_light(t_scene *scene, char **args);
int     parse_light(t_scene *scene, char **args);
int     parse_sphere(t_scene *scene, char **args);
int     parse_plane(t_scene *scene, char **args);
int     parse_cylinder(t_scene *scene, char **args);
int     verif_int(char *str, char *max);
int     verfi_float(char *str);
int     verif_fvalue(float min, float max, float value);
int     verif_str(char *str);
int	    parse_triangle(t_scene *scene, char **args);
int	    parse_ellipsoid(t_scene *scene, char **args);
void	ft_add_texture(t_data *d);

# endif
