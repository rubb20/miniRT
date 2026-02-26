/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:25:25 by isastre-          #+#    #+#             */
/*   Updated: 2026/02/26 19:05:33 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	create_ambient_light(t_miniRT *rt, char **params, bool *err)
{
	if (!check_n_params(params, 2, err))
		return ;
	rt->ambient_light.ratio = atod_err(params[1], err, 0.0, 1.0);
	rt->ambient_light.rgb = parse_color(params[2], err);
}

void	create_camera(t_miniRT *rt, char **params, bool *err)
{
	if (!check_n_params(params, 3, err))
		return ;
	rt->camera.pos = parse_3dvector(params[1], false, err);
	rt->camera.dir = parse_3dvector(params[2], true, err);
	rt->camera.fov = atoi_err(params[3], err, 0, 180);
}

void	create_light(t_miniRT *rt, char **params, bool *err)
{
	if (!check_n_params(params, 3, err))
		return ;
	rt->light.pos = parse_3dvector(params[1], false, err);
	rt->light.ratio = atod_err(params[2], err, 0.0, 1.0);
	rt->light.rgb = parse_color(params[3], err);
}
