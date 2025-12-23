/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:20:12 by isastre-          #+#    #+#             */
/*   Updated: 2025/12/22 12:18:25 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	create_element(char *line);

void	parse(t_miniRT *rt, char *filename)
{
	int		file;
	char	*line;
	char	*trimmed_line;

	file = open(filename, O_RDONLY);
	if (file < 0)
		return (error_exit(rt, OPEN_ERROR));
	while ((line = get_next_line(file)))
	{
		if (ft_is_empty(line))
			continue;
		trimmed_line = ft_strtrim(line, "\n"); // TODO check error
		create_element(trimmed_line);
		// add element to list
		free(line);
		free(trimmed_line);
	}
	close(file);
}

void	create_element(char *line)
{
	char	**params;
	char	*id;

	params = ft_split(line, ' ');
	int i = 0;
	while (params[i])
	{
		printf("param[%u] <%s>\n", i, params[i]);
		i++;
	}
	
	id = params[0];
	if (ft_equals(id, AMBIENT_LIGHT))
		create_ambient_light(params);
	else if (ft_equals(id, CAMERA))
		create_camera(params);
	else if (ft_equals(id, LIGHT))
		create_light(params);
	else if (ft_equals(id, SPHERE))
		create_sphere(params);
	else if (ft_equals(id, PLANE))
		create_plane(params);
	else if (ft_equals(id, CYLINDER))
		create_cylinder(params);
	// else error INVALID_ID_ERROR
}
