/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:43:21 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/11 21:02:25 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_3dvector	calculate_ray_direction(int x, int y, t_miniRT *scene);

/**
 * @brief creates a ray for the raytracer. A ray has a general ecuation: O+tD
 * O is origin (in this case, camera position)
 * D is direction
 * t is a variable time
 * Direction is calculated depending on the pixel we want to raytrace.
 * If we want to raytrace the center point then the direction is just forward.
 * As you move to the edge pixels the direction changes.
 * @param x pixel x position
 * @param y pixel y position
 * @param scene t_miniRT struct with information about the scene
 */
t_ray	create_ray(int x, int y, t_miniRT *scene)
{
	t_ray	ray;

	ray.origin = scene->camera.pos;
	ray.dir = calculate_ray_direction(x, y, scene);
	return (ray);
}

t_3dvector	calculate_ray_direction(int x, int y, t_miniRT *scene)
{
	float		u;
	float		v;
	float		w;
	float		h;
	t_3dvector	right;

	u = ((float)x / (float)scene->mlxinfo.width) - 0.5f;
	v = 0.5f - ((float)y / (float)scene->mlxinfo.height);
	w = 2.0f * tanf((scene->camera.fov * M_PI / 180.0f) / 2.0f);
	h = w / ((float)scene->mlxinfo.width / (float)scene->mlxinfo.height);
	right = vector_normalize(vec_cross(scene->camera.dir,
				(t_3dvector){0.0f, 1.0f, 0.0f}));
	return (vector_normalize(vector_sum(scene->camera.dir,
				vector_sum(vector_scale(right, u * w), vector_scale(
						vec_cross(right, scene->camera.dir), v * h)))));
}
