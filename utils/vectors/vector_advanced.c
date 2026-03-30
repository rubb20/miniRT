/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:01:26 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/02/26 16:38:42 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

/**
 * @brief calculates dot product
 * @return value of dot product
 */
double	vec_dot(t_3dvector a, t_3dvector b)
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
double	vec_distance(t_3dvector a, t_3dvector b)
{
	return (vector_length(vector_sub(a, b)));
}

/**
 * @brief says if a vector is unitary (is normalized)
 * @note this function tolerates a deviation lower than epsilon (bc of mantissa)
 */
bool	is_unit_vector(t_3dvector a)
{
	double	len;

	len = vector_length(a);
	return (fabs(len - 1.0) < EPSILON);
}
