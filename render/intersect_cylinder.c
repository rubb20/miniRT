/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:00:55 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/31 21:46:03 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static t_3dvector	calculate_cap(t_cylinder *cyl, int i);

static double	check_h(t_ray *ray, t_cylinder *cyl, double t)
{
	t_3dvector	hit;
	t_3dvector	oc;
	double		m;

	if (t <= 0)
		return (INFINITY);
	hit = vector_sum(ray->origin, vector_scale(ray->dir, t));
	oc = vector_sub(hit, cyl->pos);
	m = vec_dot(oc, cyl->dir);
	if (fabs(m) <= cyl->height / 2)
		return (t);
	return (INFINITY);
}

static double	get_surface_t(t_ray *ray, t_cylinder *cyl)
{
	t_3dvector	proj[2];
	double		abc[3];
	double		t[2];
	double		disc;

	proj[0] = vector_sub(ray->dir,
			vector_scale(cyl->dir, vec_dot(ray->dir, cyl->dir)));
	proj[1] = vector_sub(vector_sub(ray->origin, cyl->pos),
			vector_scale(cyl->dir, vec_dot(
					vector_sub(ray->origin, cyl->pos), cyl->dir)));
	abc[0] = vec_dot(proj[0], proj[0]);
	abc[1] = 2 * vec_dot(proj[0], proj[1]);
	abc[2] = vec_dot(proj[1], proj[1]) - pow(cyl->diameter / 2, 2);
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (INFINITY);
	t[0] = (-abc[1] - sqrt(disc)) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrt(disc)) / (2 * abc[0]);
	t[0] = check_h(ray, cyl, t[0]);
	t[1] = check_h(ray, cyl, t[1]);
	return (fmin(t[0], t[1]));
}

static double	get_cap_t(t_ray *ray, t_cylinder *cyl)
{
	double		t_cap;
	double		res;
	t_3dvector	p;
	t_3dvector	c_pos;
	int			i;

	i = 0;
	res = INFINITY;
	while (i < 2)
	{
		c_pos = calculate_cap(cyl, i);
		t_cap = vec_dot(vector_sub(c_pos, ray->origin), cyl->dir)
			/ vec_dot(ray->dir, cyl->dir);
		if (t_cap > 0)
		{
			p = vector_sub(vector_sum(ray->origin,
						vector_scale(ray->dir, t_cap)), c_pos);
			if (vec_dot(p, p) <= pow(cyl->diameter / 2, 2))
				res = fmin(res, t_cap);
		}
		i++;
	}
	return (res);
}

bool	intersect_ray_cylinder(t_ray *ray, t_cylinder *cyl, double *t)
{
	double		t_surf;
	double		t_cap;

	t_surf = get_surface_t(ray, cyl);
	t_cap = get_cap_t(ray, cyl);
	*t = fmin(t_surf, t_cap);
	return (*t > 0 && *t < INFINITY);
}

static t_3dvector	calculate_cap(t_cylinder *cyl, int i)
{
	t_3dvector	cap_pos;
	float		offset;

	if (i == 0)
		offset = -cyl->height / 2;
	else
		offset = cyl->height / 2;
	cap_pos = vector_sum(cyl->pos, vector_scale(cyl->dir, offset));
	return (cap_pos);
}
