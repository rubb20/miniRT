/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:58:25 by isastre-          #+#    #+#             */
/*   Updated: 2026/01/26 20:39:58 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

/**
 * @brief parses a str to an int and sets bool err to true if input is wrong
 */
// TODO probar casos raros
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

// TODO afinar casos raros !!!!
float	atof_err(char *str, bool *err, int min, int max)
{
	float	n;
	char	**parts;
	int		dec_len;

	if (!ft_strchr(str, '.')) // no tiene decimal
		return (atoi_err(str, err, min, max));
	
	parts = ft_split(str, '.'); // ? que pasa si 12.43. ->  // TODO da ok pero debería fallar
	if (parts == NULL || parts[2]) // error malloc o hay mas de 2 partes
	{
		*err = true;
		ft_free_str_array(parts);
		return (0);
	}

	n = atoi_err(parts[0], err, min, max);
	dec_len = ft_strlen(parts[1]);
	n += atoi_err(parts[1], err, 0, MAX_DECIMAL) / pow(10, dec_len);
	// errores?
	
	ft_free_str_array(parts);
	return (n);
}
