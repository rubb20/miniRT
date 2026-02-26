/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:08:05 by isastre-          #+#    #+#             */
/*   Updated: 2026/02/26 17:43:37 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static char	**split_and_check(char *input, bool *err);

t_color	parse_color(char *input, bool *err)
{
	t_color	color;
	char	**colors;

	colors = split_and_check(input, err);
	if (colors == NULL)
		return ((t_color){0, 0, 0});
	color.r = atoi_err(colors[0], err, 0, 255);
	color.g = atoi_err(colors[1], err, 0, 255);
	color.b = atoi_err(colors[2], err, 0, 255);
	ft_free_str_array(colors);
	return (color);
}

/**
 * @brief creates a 3dvec struct.
 * In case its normalized, sets limits [-1, 1] and checks if its unit vector
 */
t_3dvector	parse_3dvector(char *input, bool normalized, bool *err)
{
	t_3dvector	vector;
	char		**coords;
	double		min;
	double		max;

	coords = split_and_check(input, err);
	if (coords == NULL)
		return ((t_3dvector){0, 0, 0});
	if (normalized)
	{
		min = -1;
		max = 1;
	}
	else
	{
		min = DECIMAL_MIN_ACCEPTED;
		max = DECIMAL_MAX_ACCEPTED;
	}
	vector.x = atod_err(coords[0], err, min, max);
	vector.y = atod_err(coords[1], err, min, max);
	vector.z = atod_err(coords[2], err, min, max);
	ft_free_str_array(coords);
	if (normalized)
		*err = *err || !is_unit_vector(vector);
	return (vector);
}

static char	**split_and_check(char *input, bool *err)
{
	char	**splited;

	splited = ft_split(input, ',');
	if (!splited || ft_str_array_len(splited) != 3)
	{
		*err = true;
		ft_free_str_array(splited);
		return (NULL);
	}
	return (splited);
}
