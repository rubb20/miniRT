/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:54:30 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/31 19:14:49 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static bool			apply_translation(t_3dvector *rot);
static bool			apply_rotation(t_3dvector *pos);
static t_3dvector	get_input(bool *error);

bool	modify_object(t_miniRT *miniRT, int index)
{
	t_list	*node;

	node = ft_lstat(miniRT->scene, index);
	return (modify_params(get_pos(node), get_rot(node)));
}

bool	modify_params(t_3dvector *pos, t_3dvector *rot)
{
	char	*line;
	int		option;
	bool	error;

	error = false;
	if (!rot)
	{
		printf("Selected object cannot be rotated. Will apply translation.\n");
		return (apply_translation(pos));
	}
	printf("What type of transformation do you want to do?:\n");
	printf("[0] Translation\n");
	printf("[1] Rotation\n");
	line = get_next_line(0);
	line[ft_strlen(line) - 1] = '\0';
	option = atoi_err(line, &error, 0, 1);
	free(line);
	if (error)
		return (error);
	if (option == 0)
		return (apply_translation(pos));
	return (apply_rotation(rot));
}

static t_3dvector	get_input(bool *error)
{
	char		*line;
	t_3dvector	input;

	line = get_next_line(0);
	line[ft_strlen(line) - 1] = '\0';
	input = parse_3dvector(line, false, error);
	free(line);
	return (input);
}

static bool	apply_rotation(t_3dvector *rot)
{
	t_3dvector	angle;
	bool		error;

	printf("Enter rotation vector:\n");
	error = false;
	angle = get_input(&error);
	if (error)
		return (error);
	angle = vector_scale(angle, M_PI / 180);
	*rot = rotate(*rot, angle);
	return (false);
}

static bool	apply_translation(t_3dvector *pos)
{
	bool		error;
	t_3dvector	input;

	printf("Enter translation vector:\n");
	error = false;
	input = get_input(&error);
	if (error)
		return (error);
	*pos = vector_sum(*pos, input);
	return (false);
}
