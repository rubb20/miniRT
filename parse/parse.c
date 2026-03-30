/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:20:12 by isastre-          #+#    #+#             */
/*   Updated: 2026/03/30 12:55:58 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static char	**get_params(char *line, bool *err);
static void	create_element(t_miniRT *rt, char **params, bool *err);

void	parse(t_miniRT *rt, char *filename)
{
	int		file;
	char	*line;
	char	**params;
	bool	err;

	file = open(filename, O_RDONLY);
	if (file < 0)
		return (error_exit(rt, OPEN_ERROR));
	err = false;
	line = get_next_line(file);
	while (line)
	{
		params = get_params(line, &err);
		free(line);
		create_element(rt, params, &err);
		if (err)
			break ;
		line = get_next_line(file);
	}
	close(file);
	if (err)
		error_exit(rt, PARSE_ERROR);
}

static char	**get_params(char *line, bool *err)
{
	char	**params;

	if (ft_is_empty(line))
		return (NULL);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = ' ';
	printf("Parsing: %s\n", line);
	params = ft_split(line, ' ');
	if (params == NULL)
		print_and_put_error(MALLOC_ERROR, err);
	return (params);
}

static void	create_element(t_miniRT *rt, char **params, bool *err)
{
	char	*id;

	if (params == NULL || *err)
		return ;
	id = params[0];
	if (ft_equals(id, ID_AMBIENT_LIGHT))
		create_ambient_light(rt, params, err);
	else if (ft_equals(id, ID_CAMERA))
		create_camera(rt, params, err);
	else if (ft_equals(id, ID_LIGHT))
		create_light(rt, params, err);
	else if (ft_equals(id, ID_SPHERE))
		create_sphere(rt, params, err);
	else if (ft_equals(id, ID_PLANE))
		create_plane(rt, params, err);
	else if (ft_equals(id, ID_CYLINDER))
		create_cylinder(rt, params, err);
	else
		print_and_put_error(INVALID_ID, err);
	ft_free_str_array(params);
}
