/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:22:19 by isastre-          #+#    #+#             */
/*   Updated: 2025/12/01 19:24:45 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	ft_is_empty(char *string)
{
	size_t		start;

	if (string == NULL)
		return (true);
	start = 0;
	while (string[start] && ft_isspace(string[start]))
		start++;
	return (start == ft_strlen(string));
}
