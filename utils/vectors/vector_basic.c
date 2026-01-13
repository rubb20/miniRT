/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 20:45:32 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/01/13 20:13:08 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

/**
 * @brief calculates the sum of two vectors
 * @return sum vector.
 */
t_3dvector	vector_sum(t_3dvector a, t_3dvector b)
{
	return ((t_3dvector){a.x + b.x, a.y + b.y, a.z + b.z});
}

/**
 * @brief calculates the substraction of two vectors
 * @return substrated vector
 */
t_3dvector	vector_sub(t_3dvector a, t_3dvector b)
{
	return ((t_3dvector){a.x - b.x, a.y - b.y, a.z - b.z});
}

/**
 * @brief scales a vector with a factor k (can be used to multiply or divide)
 * @return scaled vector
 */
t_3dvector	vector_scale(t_3dvector a, float k)
{
	return ((t_3dvector){a.x * k, a.y * k, a.z * k});
}

/**
 * @brief calculates a vector length
 * @returns vector length
 */
float	vector_length(t_3dvector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

/**
 * @brief normalizes a vector, vector length will be 1 after the function.
 * @return normalized vector
 */
t_3dvector	vector_normalize(t_3dvector a)
{
	float	len;

	len = vector_length(a);
	if (len == 0.0f)
		return (a);
	return (vector_scale(a, 1.0f / len));
}
