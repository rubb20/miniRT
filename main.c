/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:20:03 by isastre-          #+#    #+#             */
/*   Updated: 2026/03/30 16:43:19 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	file_has_rt_extension(char *filename);

int	main(int argc, char *argv[])
{
	t_miniRT	rt;

	rt.scene = NULL;
	rt.has_ambient_light = false;
	rt.has_camera = false;
	rt.has_light = false;
	if (argc != 2 || !file_has_rt_extension(argv[1]))
		error_exit(NULL, WRONG_NUMBER_ARGS);
	parse(&rt, argv[1]);
	if (!rt.has_camera || !rt.has_light || !rt.has_ambient_light)
		error_exit(&rt, MISSING_ELEMENT);
	create_window(&rt);
	free_rt(&rt);
	return (EXIT_SUCCESS);
}

/**
 * @brief checks if a filename is .rt
 */
static bool	file_has_rt_extension(char *filename)
{
	int	len;
	int	dot_position;

	len = ft_strlen(filename);
	if (len < RTFILE_EXT_LEN)
		return (false);
	dot_position = len - RTFILE_EXT_LEN;
	return (ft_equals(filename + dot_position, RTFILE_EXT));
}

/**
 * @brief frees miniRT struct and prints error msg
 */
void	error_exit(t_miniRT *rt, char *msg)
{
	printf("Error\n%s\n", msg);
	get_next_line(-1);
	free_rt(rt);
	exit(EXIT_FAILURE);
}

/**
 * @brief frees all the miniRT allocated resources (scene & mlxinfo)
 */
void	free_rt(t_miniRT *rt)
{
	if (!rt)
		return ;
	ft_lstclear(&(rt->scene), free);
	// TODO @rub free t_mlxinfo
}
