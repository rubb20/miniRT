/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:07:11 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/31 17:44:13 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_3dvector	get_normal(t_list *hit, t_3dvector hit_point)
{
	t_cylinder	*c;
	double		m;
	t_3dvector	axis;
	t_3dvector	normal;

	if (hit->id == SPHERE)
		return (vector_normalize(vector_sub(hit_point,
					((t_sphere *)hit->obj)->pos)));
	if (hit->id == PLANE)
		return (((t_plane *)hit->obj)->dir);
	c = (t_cylinder *)hit->obj;
	axis = vector_normalize(c->dir);
	m = vec_dot(vector_sub(hit_point, c->pos), axis);
	if (m <= 0.001)
		return (vector_scale(axis, -1.0));
	if (m >= (c->height - 0.001))
		return (axis);
	normal = vector_sub(vector_sub(hit_point, c->pos), vector_scale(axis, m));
	return (vector_normalize(normal));
}
