/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:45:36 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/31 18:59:56 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static t_3dvector	rotate_x(t_3dvector origin, double angle);
static t_3dvector	rotate_y(t_3dvector origin, double angle);
static t_3dvector	rotate_z(t_3dvector origin, double angle);

t_3dvector	rotate(t_3dvector origin, t_3dvector rot)
{
	origin = rotate_x(origin, rot.x);
	origin = rotate_y(origin, rot.y);
	origin = rotate_z(origin, rot.z);
	return (origin);
}

static t_3dvector	rotate_x(t_3dvector origin, double angle)
{
	t_3dvector	result;

	result.x = origin.x;
	result.y = origin.y * cos(angle) - origin.z * sin(angle);
	result.z = origin.y * sin(angle) + origin.z * cos(angle);
	return (result);
}

static t_3dvector	rotate_y(t_3dvector origin, double angle)
{
	t_3dvector	result;

	result.x = origin.x * cos(angle) + origin.z * sin(angle);
	result.y = origin.y;
	result.z = -origin.x * sin(angle) + origin.z * cos(angle);
	return (result);
}

static t_3dvector	rotate_z(t_3dvector origin, double angle)
{
	t_3dvector	result;

	result.x = origin.x * cos(angle) - origin.y * sin(angle);
	result.y = origin.x * sin(angle) + origin.y * cos(angle);
	result.z = origin.z;
	return (result);
}
