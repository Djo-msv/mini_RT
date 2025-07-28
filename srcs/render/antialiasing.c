#include "miniRT.h"


t_ray get_antialiasing(t_scene scene, t_vec base_ray)
{
	t_cam	cam = scene.camera;
//	if (1)
//		return (create_ray(cam.coordinate, base_ray));
	t_vec dir = base_ray;

	dir.x += cam.rand_h;
	dir.y += cam.rand_v;
	dir = normalize(dir);
	return create_ray(cam.coordinate, dir);

}
