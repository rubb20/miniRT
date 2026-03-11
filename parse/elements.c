/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:22:38 by isastre-          #+#    #+#             */
/*   Updated: 2026/03/09 18:50:41 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	add_element(t_miniRT *rt, t_id id, void *element, bool *err);

void	create_sphere(t_miniRT *rt, char **params, bool *err)
{
	t_sphere	*sp;

	if (!check_n_params(params, 3, err))
		return ;

	sp = malloc(sizeof(t_sphere));
	if (sp == NULL)
		return (print_and_put_error(MALLOC_ERROR, err));

	sp->pos = parse_3dvector(params[1], false, err);
	sp->diameter = atod_err(params[2], err, DECIMAL_MIN_ACCEPTED, DECIMAL_MAX_ACCEPTED);
	sp->rgb = parse_color(params[3], err);

	add_element(rt, SPHERE, sp, err);
}

void	create_plane(t_miniRT *rt, char **params, bool *err)
{
	t_plane	*pl;

	if (!check_n_params(params, 3, err))
		return ;

	pl = malloc(sizeof(t_plane));
	if (pl == NULL)
		return (print_and_put_error(MALLOC_ERROR, err));

	pl->pos = parse_3dvector(params[1], false, err);
	pl->dir = parse_3dvector(params[2], true, err);
	pl->rgb = parse_color(params[3], err);

	add_element(rt, PLANE, pl, err);
}

void	create_cylinder(t_miniRT *rt, char **params, bool *err)
{
	t_cylinder	*cy;

	if (!check_n_params(params, 5, err))
		return ;

	cy = malloc(sizeof(t_cylinder));
	if (cy == NULL)
		return (print_and_put_error(MALLOC_ERROR, err));

	cy->pos = parse_3dvector(params[1], false, err);
	cy->dir = parse_3dvector(params[2], true, err);
	cy->diameter = atod_err(params[3], err, DECIMAL_MIN_ACCEPTED, DECIMAL_MAX_ACCEPTED);
	cy->height = atod_err(params[4], err, DECIMAL_MIN_ACCEPTED, DECIMAL_MAX_ACCEPTED);
	cy->rgb = parse_color(params[5], err);

	add_element(rt, CYLINDER, cy, err);
}

static void	add_element(t_miniRT *rt, t_id id, void *element, bool *err)
{
	t_list	*node;

	node = ft_lstnew(id, element);
	if (node == NULL)
		return (print_and_put_error(MALLOC_ERROR, err));
	ft_lstadd_back(&(rt->scene), node);
}
