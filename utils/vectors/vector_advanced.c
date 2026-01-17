/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:01:26 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/01/17 21:11:37 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

/**
 * @brief calculates dot product
 * @return value of dot product
 */
float	vec_dot(t_3dvector a, t_3dvector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/**
 * @brief calculates cross product of two vectors
 * @return cross product calculated
 */
t_3dvector	vec_cross(t_3dvector a, t_3dvector b)
{
	t_3dvector	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

/**
 * @brief calculates the distance between two vectors
 */
float	vec_distance(t_3dvector a, t_3dvector b)
{
	return (vector_length(vector_sub(a, b)));
}
