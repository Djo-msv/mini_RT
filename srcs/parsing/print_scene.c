#include "miniRT.h"

void	print_scene(t_scene scene)
{
	int i;

	i = 0;
	printf("scene :\n\n");
	printf("Ambient light range : %f\n", scene.a_light.light_ratio);
	printf("Ambient light color : %d; %d; %d\n\n", scene.a_light.color.r, scene.a_light.color.g, scene.a_light.color.b);
	printf("Camera coordonate : %f; %f; %f\n", scene.camera.coordinate.x, scene.camera.coordinate.y, scene.camera.coordinate.z);
	printf("Camera direction : %f; %f; %f\n", scene.camera.orientation.i, scene.camera.orientation.j, scene.camera.orientation.k);
	printf("Camera FOV : %f\n\n", scene.camera.fov);

	t_list	*tmp;
	t_light *light;

	tmp = scene.light;
	while (tmp)
	{
		light = (t_light *)tmp->content;
		printf("light n%d coordonate : %f; %f; %f\n", i, light->coordinate.x, light->coordinate.y, light->coordinate.z);
		printf("light n%d brightness : %f\n", i, light->bright);
		printf("light n%d colors : %d; %d; %d\n\n", i, light->color.r, light->color.g, light->color.b);
		tmp = tmp->next;
	}
	tmp = scene.sphere;
	t_sphere *sphere;
	while (tmp)
	{
		sphere = (t_sphere *)tmp->content;
		printf("Sphere n%d coordonate : %f; %f; %f\n", i, sphere->coordinate.x, sphere->coordinate.y, sphere->coordinate.z);
		printf("Sphere n%d diameter : %f\n", i, sphere->diameter);
		printf("Sphere n%d colors : %d; %d; %d\n\n", i, sphere->color.r, sphere->color.g, sphere->color.b);
		tmp = tmp->next;
	}
	tmp = scene.plane;
	t_plane *plane;
	while (tmp)
	{
		plane = (t_plane *)tmp->content;
		printf("Plane n%d coordonate : %f; %f; %f\n", i, plane->coordinate.x, plane->coordinate.y, plane->coordinate.z);
		printf("Plane n%d direction : %f; %f; %f\n", i, plane->normal.i, plane->normal.j, plane->normal.k);
		printf("Plane n%d colors : %d; %d; %d\n\n", i, plane->color.r, plane->color.g, plane->color.b);
		tmp = tmp->next;
	}
	tmp = scene.cylinder;
	t_cylinder *cylinder;
	while (tmp)
	{
		cylinder = (t_cylinder *)tmp->content;
		printf("Cylinder n%d coordonate : %f; %f; %f\n", i, cylinder->coordinate.x, cylinder->coordinate.y, cylinder->coordinate.z);
		printf("Cylinder n%d direction : %f; %f; %f\n", i, cylinder->normal.i, cylinder->normal.j, cylinder->normal.k);
		printf("Cylinder n%d diameter : %f\n", i, cylinder->diameter);
		printf("Cylinder n%d height : %f\n", i, cylinder->height);
		printf("Cylinder n%d colors : %d; %d; %d\n\n", i, cylinder->color.r, cylinder->color.g, cylinder->color.b);
		tmp = tmp->next;
	}
}
