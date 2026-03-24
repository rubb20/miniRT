/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:42:54 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/24 20:52:37 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

bool	intersect_ray_sphere(t_ray *ray, t_sphere *sphere, float *t);
bool	intersect_ray_plane(t_ray *ray, t_plane *plane, float *t);
bool	intersect_ray_cylinder(t_ray *ray, t_cylinder *cyl, float *t);

bool	intersect_object(t_ray *ray, t_list *node, float *t1);

/**
 * @brief this functions checks if a ray intersects with any object
 * in the scene. If it does, it only takes the information of the closest
 * object (the one that will be seen).
 * @param ray specific ray with origin and direction to check for intersection.
 * @param scene objects present in the scene
 * @param obj closest object as double-ptr
 *              (it is visible after the function call).
 * @return float returning t-value (O+D*t) of the ray to intersect with
 *          the closest object (obj).
 */
float	intersect(t_ray ray, t_list *scene, t_list **obj)
{
	t_list	*node;
	float	t;
	float	closest_t;

	closest_t = -1.0f;
	node = scene;
	while (node)
	{
		if (intersect_object(&ray, node, &t)
			&& (closest_t == -1.0 || (t > 0.0001f && t < closest_t)))
		{
			closest_t = t;
			if (obj != NULL)
				*obj = node;
		}
		node = node->next;
	}
	return (closest_t);
}

/**
 * @brief checks if a ray intersects with specific object.
 * @param ray to check intersection
 * @param node specific object to check intersection
 * @param t1 if it intersects with the object (return true), this float will
 *      hold the t-value.
 */
bool	intersect_object(t_ray *ray, t_list *node, float *t1)
{
	if (node->id == SPHERE && intersect_ray_sphere(ray,
			(t_sphere *)node->obj, t1))
		return (true);
	else if (node->id == PLANE && intersect_ray_plane(ray,
			(t_plane *)node->obj, t1))
		return (true);
	else if (node->id == CYLINDER && intersect_ray_cylinder(ray,
			(t_cylinder *)node->obj, t1))
		return (true);
	else
		return (false);
}

/**
 * @brief checks for intersection of a ray with a sphere
 * @param ray to check intersection.
 * @param sphere to check intersection
 * @param t if it intersects with the object (return true), this float will
 *      hold the t-value.
 */
bool	intersect_ray_sphere(t_ray *ray, t_sphere *sphere, float *t)
{
	t_3dvector	oc;
	float		a;
	float		b;
	float		c;
	float		result;

	oc = vector_sub(ray->origin, sphere->pos);
	a = vec_dot(ray->dir, ray->dir);
	b = 2.0f * vec_dot(oc, ray->dir);
	c = vec_dot(oc, oc) - (sphere->diameter / 2 * sphere->diameter / 2);
	result = b * b - 4.0f * a * c;
	if (result < 0)
		return (false);
	result = closest_object((-b - sqrt(result)) / (2.0f * a),
			(-b + sqrt(result)) / (2.0f * a));
	if (result == -1.0f)
		return (false);
	*t = result;
	return (true);
}

bool	intersect_ray_plane(t_ray *ray, t_plane *plane, float *t)
{
	t_3dvector	p0l0;
	float		denominator;
	float		result;

	denominator = vec_dot(plane->dir, ray->dir);
	if (fabs(denominator) < 1e-6)
		return (false);
	p0l0 = vector_sub(plane->pos, ray->origin);
	result = vec_dot(p0l0, plane->dir) / denominator;
	if (result < 0)
		return (false);
	*t = result;
	return (true);
}
