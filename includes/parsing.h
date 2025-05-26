#ifndef PARSING_H
# define PARSING_H

int     parse(t_data *d, int argc, char **argv);
int 	creat_scene(t_data *data, int fd);
int 	pars_camera(t_scene *scene, char **args);
int	    pars_ambient_light(t_scene *scene, char **args);
int	    pars_light(t_scene *scene, char **args);
int 	pars_sphere(t_scene *scene, char **args);
int 	pars_plane(t_scene *scene, char **args);
int	    pars_cylinder(t_scene *scene, char **args);
int 	verif_int(char *str, char *max);
int	    verfi_float(char *str);
int 	verif_fvalue(float min, float max, float value);

#endif
