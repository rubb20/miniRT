/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:20:12 by isastre-          #+#    #+#             */
/*   Updated: 2026/02/26 19:03:58 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	create_element(t_miniRT *rt, char *line, bool *err);

void	parse(t_miniRT *rt, char *filename)
{
	int		file;
	char	*line;
	char	*trimmed_line;
	bool	err;

	file = open(filename, O_RDONLY);
	if (file < 0)
		return (error_exit(rt, OPEN_ERROR));
	err = false;
	while ((line = get_next_line(file)))
	{
		if (ft_is_empty(line))
			continue;
		trimmed_line = ft_strtrim(line, "\n"); // TODO check error
		create_element(rt, trimmed_line, &err);
		// ? add element to list? o que lo haga la funcion que parsee el elemento?
		free(line);
		free(trimmed_line);
		if (err)
		{
			error_exit(rt, PARSE_ERROR);
			break; // para que haga close file
		}	
	}
	close(file);
}

void	create_element(t_miniRT *rt, char *line, bool *err)
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
	// TODO create and implement functions
	if (ft_equals(id, ID_AMBIENT_LIGHT))
		create_ambient_light(rt, params, err);
	else if (ft_equals(id, ID_CAMERA))
		create_camera(rt, params, err);
	else if (ft_equals(id, ID_LIGHT))
		create_light(rt, params, err);
	// else if (ft_equals(id, ID_SPHERE))
	// 	create_sphere(params);
	// else if (ft_equals(id, ID_PLANE))
	// 	create_plane(params);
	// else if (ft_equals(id, ID_CYLINDER))
	// 	create_cylinder(params);
	// else error INVALID_ID_ERROR
	ft_free_str_array(params);
}
