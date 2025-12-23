/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:56:15 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/12/23 16:29:35 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	destroy_window(t_window *window);

/**
 * @brief (after parsing) creates a window using minilibx, renders the picture
 * and sets up the events
 * @param scene to be rendered, already valid
 */
void create_window(t_miniRT scene)
{
	(void) scene;
	t_window window;
	int	x;
	int	y;

	window.mlx = mlx_init();
	if (window.mlx == NULL)
		error_exit(&scene, FAIL_MLX_INIT);
	mlx_get_screen_size(window.mlx, &x, &y);
	window.win = mlx_new_window(window.mlx, x - 200, y - 200, WINDOW_TITLE);
	if (window.win == NULL)
	{
		destroy_window(&window);
		error_exit(&scene, FAIL_WINDOW_CREATE);
	}
	manage_hooks(&window);
	//render
	mlx_loop(window.mlx);
	destroy_window(&window);
}

/**
 * @brief ends the execution of miniRT
 * @param window minilibx set up parameter and window pointer
 */
void destroy_window(t_window *window)
{
	if (window->mlx != NULL)
	{
		if (window->win != NULL)
			mlx_destroy_window(window->mlx, window->win);
		mlx_destroy_display(window->mlx);
		free(window->mlx);
	}
}
