/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:42:54 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/02/21 21:04:31 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

bool	intersect_object(t_ray *ray, t_list *node, float *t1);

bool	intersect_ray_sphere(t_ray *ray, t_sphere *sphere, float *t)
{
	t_3dvector	oc;
	float		a;
	float		b;
	float		c, discriminant, t2, t1;

	oc = vector_sub(ray->origin, sphere->pos);
	a = vec_dot(ray->dir, ray->dir);
	b = 2.0f * vec_dot(oc, ray->dir);
	c = vec_dot(oc, oc) - (sphere->diameter / 2 * sphere->diameter / 2);
	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0)
		return (false);
	t1 = (-b - sqrt(discriminant)) / (2.0f * a);
	t2 = (-b + sqrt(discriminant)) / (2.0f * a);
	if (t1 > 0.0001f)
		*t = t1;
	else if (t2 > 0.0001f)
		*t = t1;
	else
		return (false);
	return (true);
}

// intersect_ray_plane(&ray, (t_plane *)node->obj, &t1);
// if (t1 > 0 && t1 < closest_t) closest_t = t1;
// intersect_ray_cylinder(&ray, (t_cylinder *)node->obj, &t1, &t2);
// if (t1 > 0 && t1 < closest_t) closest_t = t1;
// if (t2 > 0 && t2 < closest_t) closest_t = t2;
float	intersect(t_ray ray, t_list *scene, t_list **obj)
{
	t_list	*node;
	float	t1;
	float	closest_t;

	closest_t = -1.0f;
	node = scene;
	while (node)
	{
		if (intersect_object(&ray, node, &t1)
			&& (closest_t == -1.0 || (t1 > 0.0001f && t1 < closest_t)))
		{
			closest_t = t1;
			*obj = node;
		}
		node = node->next;
	}
	return (closest_t);
}

bool	intersect_object(t_ray *ray, t_list *node, float *t1)
{
	if (node->id == SPHERE && intersect_ray_sphere(ray,
			(t_sphere *)node->obj, t1))
		return (true);
	else if (node->id == PLANE)
		return (true);
	else if (node->id == CYLINDER)
		return (true);
	else
		return (false);
}
