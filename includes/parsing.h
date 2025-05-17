#ifndef PARSING_H
# define PARSING_H

void	creat_scene(t_data *data, int fd);
int		pars_camera(t_scene *scene, char **args);
int		pars_ambient_light(t_scene *scene, char **args);
int		pars_light(t_scene *scene, char **args);
int		pars_sphere(t_scene *scene, char **args);
int		pars_plane(t_scene *scene, char **args);
int		pars_cylinder(t_scene *scene, char **args);


#endif // !PARSING_H



