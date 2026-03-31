/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:34:31 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/31 19:03:18 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static int	end_loop_hook(t_mlxinfo *window);
static int	key_hook(int keycode, t_miniRT *miniRT);
static bool	modify_scene_hook(t_miniRT *miniRT);

/**
 * @brief sets up the handler functions for specific events (mouse click/
 * 			keyboard press or closing the window)
 * @param window pointer for minilibx created window
 */
void	manage_hooks(t_miniRT *miniRT)
{
	mlx_hook(miniRT->mlxinfo.win, CLOSE_WINDOW, 0,
		end_loop_hook, &miniRT->mlxinfo);
	mlx_key_hook(miniRT->mlxinfo.win, key_hook, miniRT);
}

/**
 * @brief keyboard pressed event handler.
 * @param keycode code for the specific pressed key
 * @param window pointer for minilibx created window
 */
int	key_hook(int keycode, t_miniRT *miniRT)
{
	if (keycode == XK_Escape)
		end_loop_hook(&miniRT->mlxinfo);
	if (keycode == XK_M || keycode == XK_m)
	{
		if (!modify_scene_hook(miniRT))
			render(miniRT);
	}
	return (0);
}

/**
 * @brief ends up the loop for the window
 * @param window pointer for minilibx created window
 */
static int	end_loop_hook(t_mlxinfo *window)
{
	mlx_loop_end(window->mlx);
	return (0);
}

static bool	modify_scene_hook(t_miniRT *miniRT)
{
	int		list_len;
	char	*line;
	int		index;
	bool	error;

	list_len = print_all_scene(miniRT);
	printf("Choose the index of the object to transform:\n");
	line = get_next_line(0);
	error = false;
	line[ft_strlen(line) - 1] = '\0';
	index = atoi_err(line, &error, 0, list_len + 1);
	free(line);
	if (error)
		return (true);
	if (index >= 0 && index < list_len)
		return (modify_object(miniRT, index));
	else if (index == list_len)
		return (modify_params(&miniRT->camera.pos, &miniRT->camera.dir));
	else if (index == list_len + 1)
		return (modify_params(&miniRT->light.pos, NULL));
	return (false);
}
