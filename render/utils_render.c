/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:13 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/02/21 21:13:06 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_color get_color(t_list lst)
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
    return (c.r << 16) | (c.g << 8) | (c.b);
}
