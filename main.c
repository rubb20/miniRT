/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:20:03 by isastre-          #+#    #+#             */
/*   Updated: 2025/12/23 14:03:27 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	file_has_rt_extension(char *filename);

int main(int argc, char *argv[])
{
	t_miniRT	rt;

	if (argc != 2 || !file_has_rt_extension(argv[1]))
		error_exit(NULL, WRONG_NUMBER_ARGS);
	parse(&rt, argv[1]);
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
	// free miniRT
	(void) rt;
	exit(EXIT_FAILURE);
}
