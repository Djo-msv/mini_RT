#include "miniRT.h"

// void	print_scene(t_scene scene)
// {
// 	int i;

// 	i = 0;
// 	printf("scene :\n\n");
// 	printf("Ambient light range : %f\n", scene.a_light.range);
// 	printf("Ambient light color : %d; %d; %d\n\n", scene.a_light.color.r, scene.a_light.color.g, scene.a_light.color.b);
// 	printf("Camera coordonate : %f; %f; %f\n", scene.camera.coordinate.x, scene.camera.coordinate.y, scene.camera.coordinate.z);
// 	printf("Camera direction : %f; %f; %f\n", scene.camera.orientation.i, scene.camera.orientation.j, scene.camera.orientation.k);
// 	printf("Camera FOV : %f\n\n", scene.camera.fov);
// 	// while (scene.light.isset == true)
// 	// {
// 		printf("light n%d coordonate : %f; %f; %f\n", i, scene.light.coordinate.x, scene.light.coordinate.y, scene.light.coordinate.z);
// 		printf("light n%d brightness : %f\n", i, scene.light.bright);
// 		printf("light n%d colors : %d; %d; %d\n\n", i, scene.light.color.r, scene.light.color.g, scene.light.color.b);
// 	// }
// 	// while (scene.sphere.isset == true)
// 	// {
// 		printf("Sphere n%d coordonate : %f; %f; %f\n", i, scene.sphere.coordinate.x, scene.sphere.coordinate.y, scene.sphere.coordinate.z);
// 		printf("Sphere n%d diameter : %f\n", i, scene.sphere.diameter);
// 		printf("Sphere n%d colors : %d; %d; %d\n\n", i, scene.sphere.color.r, scene.sphere.color.g, scene.sphere.color.b);
// 	// }
// 	// while (scene.plane.isset == true)
// 	// {
// 		printf("Plane n%d coordonate : %f; %f; %f\n", i, scene.plane.coordinate.x, scene.plane.coordinate.y, scene.plane.coordinate.z);
// 		printf("Plane n%d direction : %f; %f; %f\n", i, scene.plane.normal.i, scene.plane.normal.j, scene.plane.normal.k);
// 		printf("Plane n%d colors : %d; %d; %d\n\n", i, scene.plane.color.r, scene.plane.color.g, scene.plane.color.b);
// 	// }
// 	// while (scene.cylinder.isset == true)
// 	// {
// 		printf("Cylinder n%d coordonate : %f; %f; %f\n", i, scene.cylinder.coordinate.x, scene.cylinder.coordinate.y, scene.cylinder.coordinate.z);
// 		printf("Cylinder n%d direction : %f; %f; %f\n", i, scene.cylinder.normal.i, scene.cylinder.normal.j, scene.cylinder.normal.k);
// 		printf("Cylinder n%d diameter : %f\n", i, scene.cylinder.diameter);
// 		printf("Cylinder n%d height : %f\n", i, scene.cylinder.height);
// 		printf("Cylinder n%d colors : %d; %d; %d\n\n", i, scene.cylinder.color.r, scene.cylinder.color.g, scene.cylinder.color.b);
// 	// }

// }
