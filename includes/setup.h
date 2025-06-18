#ifndef SETUP_H
# define SETUP_H

typedef struct s_scene
{
	t_a_light	a_light;
	t_cam		camera;
	t_list		*light;
	t_list		*sphere;
	t_list		*plane;
	t_list		*cylinder;
}	t_scene
__attribute__((aligned(1)));

typedef struct s_data
{
//	t_mlx		mlx;
	t_scene		scene;
//	t_setting_cam	setting_cam;
//	t_render_image	image;
}t_data
__attribute__((aligned(1)));

#endif
