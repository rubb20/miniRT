/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:43:21 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/02/21 21:18:47 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_ray	create_ray(int x, int y, t_miniRT *scene)
{
	t_ray ray;
	float aspect;
	float u, v, w, h;
	t_3dvector right, up;

	ray.origin = scene->camera.pos;
	aspect = (float)scene->mlxinfo.width / (float)scene->mlxinfo.height;
	u = ((float)x / (float)scene->mlxinfo.width) - 0.5f;
	v = 0.5f - ((float)y / (float)scene->mlxinfo.height);
	w = 2.0f * tanf((scene->camera.fov * M_PI / 180.0f) / 2.0f);
	h = w / aspect;
	right = vector_normalize(vec_cross(scene->camera.dir,
		(t_3dvector){0.0f, 1.0f, 0.0f}));
	up = vec_cross(right, scene->camera.dir);
	ray.dir = vector_sum(scene->camera.dir,
			vector_sum(vector_scale(right, u * w), vector_scale(up, v * h)));
	ray.dir = vector_normalize(ray.dir);
	return (ray);
}
