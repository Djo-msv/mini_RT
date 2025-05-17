#include "miniRT.h"

void	print_scene(t_scene scene)
{
	printf("scene :\n\n");
	printf("Ambient light range : %f\n", scene.a_light.range);
	printf("Ambient light color : %d; %d; %d\n\n", scene.a_light.r, scene.a_light.g, scene.a_light.b);
	printf("Camera coordonate : %f; %f; %f\n", scene.camera.x, scene.camera.y, scene.camera.z);
	printf("Camera direction : %f; %f; %f\n", scene.camera.orient_x, scene.camera.orient_y, scene.camera.orient_z);
	printf("Camera FOV : %f\n", scene.camera.fov);
}
