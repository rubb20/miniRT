/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:56:15 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/01/16 21:27:35 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	destroy_window(t_mlxinfo *window);

/**
 * @brief (after parsing) creates a window using minilibx, renders the picture
 * and sets up the events
 * @param scene to be rendered, already valid
 */
void	create_window(t_miniRT scene)
{
	t_mlxinfo	window;

	window.mlx = mlx_init();
	if (window.mlx == NULL)
		error_exit(&scene, FAIL_MLX_INIT);
	mlx_get_screen_size(window.mlx, &window.width, &window.height);
	window.win = mlx_new_window(window.mlx, window.width - 200,
			window.height - 200, WINDOW_TITLE);
	if (window.win == NULL)
	{
		destroy_window(&window);
		error_exit(&scene, FAIL_WINDOW_CREATE);
	}
	scene.mlxinfo = window;
	manage_hooks(&window);
	//render
	mlx_loop(window.mlx);
	destroy_window(&window);
}

/**
 * @brief ends the execution of miniRT
 * @param window minilibx set up parameter and window pointer
 */
static void	destroy_window(t_mlxinfo *window)
{
	if (window->mlx == NULL)
		return ;
	if (window->win != NULL)
		mlx_destroy_window(window->mlx, window->win);
	mlx_destroy_display(window->mlx);
	free(window->mlx);
}
