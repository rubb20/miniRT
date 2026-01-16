/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:08:05 by isastre-          #+#    #+#             */
/*   Updated: 2025/12/23 18:05:05 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_color	*create_color(char *input)
{
	t_color	*color;
	char	*colors;

	color = ft_calloc(1, sizeof(t_color)); // TODO error
	colors = ft_split(input, ","); // TODO error

	color->r = ft_atoi(colors[0]);
	color->g = ft_atoi(colors[1]);
	color->b = ft_atoi(colors[2]);
	free(colors);
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
	free(coords);
	return (vector);
}
