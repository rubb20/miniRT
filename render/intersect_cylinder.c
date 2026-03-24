/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:00:55 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/24 21:24:18 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static float	check_h(t_ray *ray, t_cylinder *cyl, t_3dvector v, float t)
{
	t_3dvector	hit;
	t_3dvector	oc;
	float		m;

	if (t <= 0)
		return (1e30f);
	hit = vector_sum(ray->origin, vector_scale(ray->dir, t));
	oc = vector_sub(hit, cyl->pos);
	m = vec_dot(oc, v);
	if (m >= 0 && m <= cyl->height)
		return (t);
	return (1e30f);
}

static float	get_surface_t(t_ray *ray, t_cylinder *cyl, t_3dvector v)
{
	t_3dvector	proj[2];
	float		abc[3];
	float		t[2];
	float		disc;

	proj[0] = vector_sub(ray->dir, vector_scale(v, vec_dot(ray->dir, v)));
	proj[1] = vector_sub(vector_sub(ray->origin, cyl->pos),
		vector_scale(v, vec_dot(vector_sub(ray->origin, cyl->pos), v)));
	abc[0] = vec_dot(proj[0], proj[0]);
	abc[1] = 2 * vec_dot(proj[0], proj[1]);
	abc[2] = vec_dot(proj[1], proj[1]) - pow(cyl->diameter / 2, 2);
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (1e30f);
	t[0] = (-abc[1] - sqrtf(disc)) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrtf(disc)) / (2 * abc[0]);
	t[0] = check_h(ray, cyl, v, t[0]);
	t[1] = check_h(ray, cyl, v, t[1]);
	if (t[0] < t[1])
		return (t[0]);
	return (t[1]);
}

static float	get_cap_t(t_ray *ray, t_cylinder *cyl, t_3dvector v)
{
	float		t_cap;
	float		res;
	t_3dvector	p;
	t_3dvector	c_pos;
	int			i;

	i = -1;
	res = 1e30f;
	while (++i < 2)
	{
		c_pos = vector_sum(cyl->pos, vector_scale(v, i * cyl->height));
		t_cap = vec_dot(vector_sub(c_pos, ray->origin), v) /
			vec_dot(ray->dir, v);
		if (t_cap > 0)
		{
			p = vector_sub(vector_sum(ray->origin,
				vector_scale(ray->dir, t_cap)), c_pos);
			if (vec_dot(p, p) <= pow(cyl->diameter / 2, 2))
				res = fminf(res, t_cap);
		}
	}
	return (res);
}

bool	intersect_ray_cylinder(t_ray *ray, t_cylinder *cyl, float *t)
{
	t_3dvector	v;
	float		t_surf;
	float		t_cap;

	v = vector_normalize(cyl->dir);
	t_surf = get_surface_t(ray, cyl, v);
	t_cap = get_cap_t(ray, cyl, v);
	*t = fminf(t_surf, t_cap);
	return (*t > 0 && *t < 1e30f);
}
