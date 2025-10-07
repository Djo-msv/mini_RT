/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:22:10 by star              #+#    #+#             */
/*   Updated: 2025/10/01 20:42:47 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

// Fonction pour obtenir les coordonnées UV sur la sphère
t_vec2	sphere_get_uv(t_vec point, t_vec center, float radius)
{
	t_vec2	uv;
	t_vec	p;
	float	theta;
	float	phi;

	// Normaliser le point sur la sphère
	p = vec_sub(point, center);
	p = normalize(p);
	
	// Coordonnées sphériques
	theta = acos(-p.y);  // 0 à π
	phi = atan2(-p.z, p.x) + M_PI;  // 0 à 2π
	
	// Conversion en UV (0 à 1)
	uv.x = phi / (2.0 * M_PI);
	uv.y = theta / M_PI;
	(void)radius;
	
	return (uv);
}

// Fonction pour lire la hauteur depuis la heightmap
float	get_height_from_map(mlx_context mlx, t_sphere *sphere, t_vec2 uv)
{
	int		x;
	int		y;
	mlx_color		pixel;
	unsigned char	r;

	// Wrapper les coordonnées UV (pour les textures répétées)
	uv.x = fmod(uv.x, 1.0);
	if (uv.x < 0)
		uv.x += 1.0;
	uv.y = fmod(uv.y, 1.0);
	if (uv.y < 0)
		uv.y += 1.0;
	
	// Convertir UV en coordonnées pixel
	x = (int)(uv.x * (sphere->tex.width - 1));
	y = (int)(uv.y * (sphere->tex.height - 1));
	
	// Limiter les coordonnées
	if (x < 0) x = 0;
	if (x >= sphere->tex.width) x = sphere->tex.width - 1;
	if (y < 0) y = 0;
	if (y >= sphere->tex.height) y = sphere->tex.height - 1;
	
	// Lire le pixel
	pixel = mlx_get_image_pixel(mlx, sphere->tex.h_image, x, y);
	
	// Extraire la composante rouge (ou moyenne RGB selon ton besoin)
	r = pixel.r;
	
	// Normaliser entre 0 et 1
	return (r / 255.0);
}


// Version ray marching (plus précise)
float	hit_sphere_heightmap(t_scene scene, t_sphere *sphere, t_ray r)
{
	t_vec	abc;
	t_vec	oc;
	float	discriminant;
	float	t_min;
	float	t_max;
	float	t;
	int		steps;

	if (sphere->radius <= 0)
		return (-1);
	// 1. Intersection avec sphère élargie (bounding volume)
//	float max_displacement = (sphere->displacement * 0.5);
	float max_displacement = (0.5 * 0.5);
	float bounding_radius = sphere->radius + max_displacement;
	
	oc = vec_sub(sphere->coordinate, r.origin);
	abc.x = scalar_product(r.direction, r.direction);
	abc.y = scalar_product(r.direction, oc);
	abc.z = scalar_product(oc, oc) - bounding_radius * bounding_radius;
	discriminant = abc.y * abc.y - abc.x * abc.z;
	
	if (discriminant < 0.0)
		return (-1.0);
	
	// Calculer t_min et t_max
	t_min = (abc.y - sqrt(discriminant)) / abc.x;
	t_max = (abc.y + sqrt(discriminant)) / abc.x;
	
	if (t_max < 0.001)
		return (-1.0);
	if (t_min < 0.001)
		t_min = 0.001;
	
	// 2. Ray marching entre t_min et t_max
	t = t_min;
	steps = 0;
	int max_steps = 4048;  // Limite d'itérations
	
	while (t < t_max && steps < max_steps)
	{
		t_vec	point;
		t_vec2	uv;
		float	height;
		float	displaced_radius;
		t_vec	to_center;
		float	dist_to_center;
		float	dist;
		
		// Point actuel sur le rayon
		point = vec_add(r.origin, vec_scale(r.direction, t));
		
		// Distance au centre
		to_center = vec_sub(point, sphere->coordinate);
		dist_to_center = length(to_center);
		
		// Calculer UV et hauteur
		uv = sphere_get_uv(point, sphere->coordinate, sphere->radius);
		height = get_height_from_map(scene.mlx->mlx, sphere, uv);
		
		// Rayon déplacé à cette position
		displaced_radius = sphere->radius + (height - 0.5) * 0.5f; // scale
		
		// Distance signée à la surface déplacée
		dist = dist_to_center - displaced_radius;
		
		// Si on est assez proche de la surface
		if (fabs(dist) < 0.05)
			return (t);
		
		// Avancer le long du rayon (sphere tracing)
		// On peut avancer de la distance à la surface (optimisation)
		t += fmax(0.001, fabs(dist) * 0.2);
		steps++;
	}
	
	return (-1.0);
}


