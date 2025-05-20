#include "miniRT.h"

void	print_scene(t_scene scene)
{
	int	i;

	printf("scene :\n\n");
	printf("Ambient light range : %f\n", scene.a_light.range);
	printf("Ambient light color : %d; %d; %d\n\n", scene.a_light.r, scene.a_light.g, scene.a_light.b);
	printf("Camera coordonate : %f; %f; %f\n", scene.camera.x, scene.camera.y, scene.camera.z);
	printf("Camera direction : %f; %f; %f\n", scene.camera.orient_x, scene.camera.orient_y, scene.camera.orient_z);
	printf("Camera FOV : %f\n\n", scene.camera.fov);
	i = 0;
	while (scene.light[i].isset == true)
	{
		printf("light n%d coordonate : %f; %f; %f\n", i, scene.light[i].x, scene.light[i].y, scene.light[i].z);
		printf("light n%d brightness : %f\n", i, scene.light[i].bright);
		printf("light n%d colors : %d; %d; %d\n\n", i, scene.light[i].r, scene.light[i].g, scene.light[i].b);
		i++;
	}
	i = 0;
	while (scene.sphere[i].isset == true)
	{
		printf("Sphere n%d coordonate : %f; %f; %f\n", i, scene.sphere[i].x, scene.sphere[i].y, scene.sphere[i].z);
		printf("Sphere n%d diameter : %f\n", i, scene.sphere[i].d);
		printf("Sphere n%d colors : %d; %d; %d\n\n", i, scene.sphere[i].r, scene.sphere[i].g, scene.sphere[i].b);
		i++;
	}
	i = 0;
	while (scene.plane[i].isset == true)
	{
		printf("Plane n%d coordonate : %f; %f; %f\n", i, scene.plane[i].x, scene.plane[i].y, scene.plane[i].z);
		printf("Plane n%d direction : %f; %f; %f\n", i, scene.plane[i].normal_x, scene.plane[i].normal_y, scene.plane[i].normal_z);
		printf("Plane n%d colors : %d; %d; %d\n\n", i, scene.plane[i].r, scene.plane[i].g, scene.plane[i].b);
		i++;
	}
	i = 0;
	while (scene.cylinder[i].isset == true)
	{
		printf("Cylinder n%d coordonate : %f; %f; %f\n", i, scene.cylinder[i].x, scene.cylinder[i].y, scene.cylinder[i].z);
		printf("Cylinder n%d direction : %f; %f; %f\n", i, scene.cylinder[i].normal_x, scene.cylinder[i].normal_y, scene.cylinder[i].normal_z);
		printf("Cylinder n%d diameter : %f\n", i, scene.cylinder[i].d);
		printf("Cylinder n%d height : %f\n", i, scene.cylinder[i].height);
		printf("Cylinder n%d colors : %d; %d; %d\n\n", i, scene.cylinder[i].r, scene.cylinder[i].g, scene.cylinder[i].b);
		i++;
	}

}
