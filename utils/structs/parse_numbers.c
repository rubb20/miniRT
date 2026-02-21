/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:58:25 by isastre-          #+#    #+#             */
/*   Updated: 2026/02/21 20:49:58 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static int	get_sign(char **str);
static int	get_num(char **str, bool *err, int max_len);
static bool	is_unexpected(double n, char *str, double min, double max);

/**
 * WRONG INPUTS:
 * - numbers smaller or bigger than MIN or MAX INT
 * - numbers with more than DECIMAL_MAX_LEN decimals
 * - numbers with more than one sign (+-, --, ...) or dot (.)
 * - string that contains something different from digits, dot and sign
 */

/**
 * @brief parses a str to int and sets bool err to true if input is wrong
 */
int	atoi_err(char *str, bool *err, int min, int max)
{
	long	n;
	int		sign;

	sign = get_sign(&str);
	n = get_num(&str, err, INT_MAX_LEN) * sign;
	*err = *err || is_unexpected(n, str, min, max);
	return (n);
}

/**
 * @brief parses a str to double and sets bool err to true if input is wrong
 * @details 1st get_num gets int part, 2nd gets decimal part
 */
double	atod_err(char *str, bool *err, double min, double max)
{
	double	n;
	int		sign;
	int		dec_len;

	sign = get_sign(&str);
	n = get_num(&str, err, INT_MAX_LEN);
	if (*str && *str != '.')
		*err = true;
	if (!*str || *err == true)
		return (n * sign);
	str++;
	dec_len = ft_strlen(str);
	n += get_num(&str, err, DECIMAL_MAX_LEN) / pow(10, dec_len);
	n *= sign;
	*err = *err || is_unexpected(n, str, min, max);
	return (n);
}

/**
 * @brief parses the sign of the number
 */
static int	get_sign(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
		sign = -1;
	if (**str == '+' || **str == '-')
		(*str)++;
	return (sign);
}

/**
 * @brief parses the units of the number
 */
static int	get_num(char **str, bool *err, int max_len)
{
	long	n;

	if (!**str || !ft_isdigit(**str))
	{
		*err = true;
		return (0);
	}
	n = 0;
	while (ft_isdigit(**str) && max_len)
	{
		n = n * 10 + (**str - '0');
		(*str)++;
		max_len--;
	}
	return (n);
}

/**
 * @brief checks if the number is valid or not given the possible min and max
 * @returns true if its unvalid and false if its correct
 */
static bool	is_unexpected(double n, char *str, double min, double max)
{
	return (n > max || n < min || *str);
}
