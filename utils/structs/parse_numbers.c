/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:58:25 by isastre-          #+#    #+#             */
/*   Updated: 2025/12/23 19:23:29 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

/**
 * @brief parses a str to an int and sets bool err to true if input is wrong
 */
int	atoi_err(char *str, bool *err, int min, int max)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	if (ft_strlen(str) > 11)
	{
		*err = true;
		return (0);
	}
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	if (n * sign > max || n * sign < min || *str)
		*err = true;
	return (n * sign);
}