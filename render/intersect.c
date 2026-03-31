/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:42:54 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/31 17:30:39 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static bool		intersect_ray_sphere(t_ray *ray, t_sphere *sphere, double *t);
static bool		intersect_ray_plane(t_ray *ray, t_plane *plane, double *t);
static bool		intersect_object(t_ray *ray, t_list *node, double *t1);
static double	closest_object(double t1, double t2);

/**
 * @brief this functions checks if a ray intersects with any object
 * in the scene. If it does, it only takes the information of the closest
 * object (the one that will be seen).
 * @param ray specific ray with origin and direction to check for intersection.
 * @param scene objects present in the scene
 * @param obj closest object as double-ptr
 *              (it is visible after the function call).
 * @return double returning t-value (O+D*t) of the ray to intersect with
 *          the closest object (obj).
 */
double	intersect(t_ray ray, t_list *scene, t_list **obj)
{
	t_list	*node;
	double	t;
	double	closest_t;

	closest_t = -1.0;
	node = scene;
	while (node)
	{
		if (intersect_object(&ray, node, &t)
			&& (closest_t == -1.0 || (t > 0.0001 && t < closest_t)))
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
 * @param t1 if it intersects with the object (return true), this double will
 *      hold the t-value.
 */
static bool	intersect_object(t_ray *ray, t_list *node, double *t1)
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
 * @param t if it intersects with the object (return true), this double will
 *      hold the t-value.
 */
static bool	intersect_ray_sphere(t_ray *ray, t_sphere *sphere, double *t)
{
	t_3dvector	oc;
	double		a;
	double		b;
	double		c;
	double		result;

	oc = vector_sub(ray->origin, sphere->pos);
	a = vec_dot(ray->dir, ray->dir);
	b = 2.0 * vec_dot(oc, ray->dir);
	c = vec_dot(oc, oc) - (sphere->diameter / 2 * sphere->diameter / 2);
	result = b * b - 4.0 * a * c;
	if (result < 0)
		return (false);
	result = closest_object((-b - sqrt(result)) / (2.0 * a),
			(-b + sqrt(result)) / (2.0 * a));
	if (result == -1.0)
		return (false);
	*t = result;
	return (true);
}

static bool	intersect_ray_plane(t_ray *ray, t_plane *plane, double *t)
{
	t_3dvector	p0l0;
	double		denominator;
	double		result;

	denominator = vec_dot(plane->dir, ray->dir);
	if (fabs(denominator) < EPSILON)
		return (false);
	p0l0 = vector_sub(plane->pos, ray->origin);
	result = vec_dot(p0l0, plane->dir) / denominator;
	if (result < 0)
		return (false);
	*t = result;
	return (true);
}

static double	closest_object(double t1, double t2)
{
	if (t1 > 0 && t2 > 0)
		return (fmin(t1, t2));
	else if (t1 > 0)
		return (t1);
	else if (t2 > 0)
		return (t2);
	return (-1.0);
}
