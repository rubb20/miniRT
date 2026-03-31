/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:03:07 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/31 15:04:55 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_list	*ft_lstat(t_list *lst, int index)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (NULL);
	while (lst->next && i < index)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
