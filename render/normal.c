/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:07:11 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/11 20:28:14 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_3dvector	get_normal(t_list *hit, t_3dvector hit_point)
{
	t_cylinder	*c;
	float		m;
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
	if (m <= 0.001f)
		return (vector_scale(axis, -1.0f));
	if (m >= (c->height - 0.001f))
		return (axis);
	normal = vector_sub(vector_sub(hit_point, c->pos), vector_scale(axis, m));
	return (vector_normalize(normal));
}
