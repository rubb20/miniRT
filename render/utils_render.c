/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:13 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/02/26 20:26:55 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_color	get_color(t_list lst)
{
	if (lst.id == SPHERE)
		return (((t_sphere *)lst.obj)->rgb);
	else if (lst.id == PLANE)
		return (((t_plane *)lst.obj)->rgb);
	else
		return (((t_cylinder *)lst.obj)->rgb);
}

int	color_to_int(t_color c)
{
	return ((c.r << 16) | (c.g << 8) | (c.b));
}

t_color	fminf_color(t_color color1, t_color color2, int max)
{
	t_color	result;

	result.r = fminf(color1.r + color2.r, max);
	result.g = fminf(color1.g + color2.g, max);
	result.b = fminf(color1.b + color2.b, max);
	return (result);
}

t_color	apply_light(t_color obj, float intensity, t_color light_color)
{
	t_color	diffuse;

	diffuse.r = obj.r * intensity * (light_color.r / 255.0f);
	diffuse.g = obj.g * intensity * (light_color.g / 255.0f);
	diffuse.b = obj.b * intensity * (light_color.b / 255.0f);
	return (diffuse);
}

float	closest_object(float t1, float t2)
{
	if (t1 > 0 && t2 > 0)
		return (fminf(t1, t2));
	else if (t1 > 0)
		return (t1);
	else if (t2 > 0)
		return (t2);
	return (-1.0f);
}
