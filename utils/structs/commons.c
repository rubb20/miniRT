/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:08:05 by isastre-          #+#    #+#             */
/*   Updated: 2026/01/16 21:06:51 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_color	*create_color(char *input)
{
	t_color	*color;
	char	*colors;
	bool	err;

	color = ft_calloc(1, sizeof(t_color)); // TODO error
	colors = ft_split(input, ","); // TODO error

	err = false;
	color->r = atoi_err(colors[0], &err, 0, 255);
	color->g = atoi_err(colors[1], &err, 0, 255);
	color->b = atoi_err(colors[2], &err, 0, 255);

	ft_free_str_array(colors);
	// TODO tratar atoi error en caso de que haya
	return (color);
}

t_3dvector	*create_3dvector(char *input)
{
	t_3dvector	*vector;
	char		*coords;

	vector = ft_calloc(1, sizeof(t_3dvector)); // TODO error
	coords = ft_split(input, ","); // TODO error
	
	// TODO atof
	vector->x = ft_atof(coords[0]);
	vector->y = ft_atof(coords[1]);
	vector->z = ft_atof(coords[2]);
	ft_free_str_array(coords);
	return (vector);
}
