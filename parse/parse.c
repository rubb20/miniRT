/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:20:12 by isastre-          #+#    #+#             */
/*   Updated: 2026/02/26 21:26:51 by isastre-         ###   ########.fr       */
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
	while ((line = get_next_line(file))) // TODO error gnl? y cambiar por norminette
	{
		printf("line: %s\n", line);
		params = get_params(line, &err);
		free(line);
		create_element(rt, params, &err);
		if (err)
		{
			close(file);
			error_exit(rt, PARSE_ERROR);
		}	
	}
	close(file);
}

static char	**get_params(char *line, bool *err)
{
	char	*trimmed_line;
	char	**params;

	if (ft_is_empty(line))
		return (NULL);
	trimmed_line = ft_strtrim(line, "\n");
	if (trimmed_line == NULL)
	{
		print_and_put_error(MALLOC_ERROR, err);
		return (NULL);
	}
	params = ft_split(trimmed_line, ' ');
	if (params == NULL)
		print_and_put_error(MALLOC_ERROR, err);
	free(trimmed_line);
	return (params);

}

static void	create_element(t_miniRT *rt, char **params, bool *err)
{
	char	*id;

	if (params == NULL || *err)
		return  ;
	
	int i = 0;
	while (params[i])
	{
		printf("param[%u] <%s>\n", i, params[i]);
		i++;
	}
	
	id = params[0];
	if (ft_equals(id, ID_AMBIENT_LIGHT))
		create_ambient_light(rt, params, err);
	else if (ft_equals(id, ID_CAMERA))
		create_camera(rt, params, err);
	else if (ft_equals(id, ID_LIGHT))
		create_light(rt, params, err);
	// TODO implementar. La funcion que crea el elemento lo añade a la lista
	// else if (ft_equals(id, ID_SPHERE))
	// 	create_sphere(params);
	// else if (ft_equals(id, ID_PLANE))
	// 	create_plane(params);
	// else if (ft_equals(id, ID_CYLINDER))
	// 	create_cylinder(params);
	else
		print_and_put_error(INVALID_ID, err);
	ft_free_str_array(params);
}
