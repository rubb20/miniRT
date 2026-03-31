/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_modify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:04:07 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/31 18:59:00 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

char	*get_name(t_list *lst)
{
	if (lst->id == SPHERE)
		return ("Sphere");
	else if (lst->id == PLANE)
		return ("Plane");
	else if (lst->id == CYLINDER)
		return ("Cylinder");
	return ("");
}

t_3dvector	*get_pos(t_list *lst)
{
	if (lst->id == SPHERE)
		return (&((t_sphere *)lst->obj)->pos);
	else if (lst->id == PLANE)
		return (&((t_plane *)lst->obj)->pos);
	else if (lst->id == CYLINDER)
		return (&((t_cylinder *)lst->obj)->pos);
	return (NULL);
}

t_3dvector	*get_rot(t_list *lst)
{
	if (lst->id == PLANE)
		return (&((t_plane *)lst->obj)->dir);
	else if (lst->id == CYLINDER)
		return (&((t_cylinder *)lst->obj)->dir);
	return (NULL);
}

int	print_all_scene(t_miniRT *miniRT)
{
	int		list_len;
	t_list	*list;

	list_len = 0;
	list = miniRT->scene;
	printf("The objects in the scene are:\n");
	while (list != NULL)
	{
		printf("[%d] %s\n", list_len, get_name(list));
		list = list->next;
		list_len++;
	}
	printf("[%d] Camera\n", list_len);
	printf("[%d] Light\n", list_len + 1);
	return (list_len);
}
