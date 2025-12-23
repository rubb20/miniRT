/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:34:31 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/12/23 16:25:18 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	end_loop_hook(t_window *window);
int	key_hook(int keycode, t_window *window);

/**
 * @brief sets up the handler functions for specific events (mouse click/
 * 			keyboard press or closing the window)
 * @param window pointer for minilibx created window
 */
void manage_hooks(t_window *window)
{
	mlx_hook(window->win, 17, 0, end_loop_hook, window);
	mlx_key_hook(window->win, key_hook, window);
}

/**
 * @brief ends up the loop for the window
 * @param window pointer for minilibx created window
 */
int end_loop_hook(t_window *window)
{
	mlx_loop_end(window->mlx);
	return (0);
}

/**
 * @brief keyboard pressed event handler.
 * @param keycode code for the specific pressed key
 * @param window pointer for minilibx created window
 */
int key_hook(int keycode, t_window *window)
{
	if (keycode == XK_Escape)
		end_loop_hook(window);
	return (0);
}
