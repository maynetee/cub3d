/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 23:22:24 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/19 23:22:28 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		game->keys.esc = 1;
	else if (keycode == W_KEY)
		game->keys.w = 1;
	else if (keycode == A_KEY)
		game->keys.a = 1;
	else if (keycode == S_KEY)
		game->keys.s = 1;
	else if (keycode == D_KEY)
		game->keys.d = 1;
	else if (keycode == LEFT_KEY)
		game->keys.left = 1;
	else if (keycode == RIGHT_KEY)
		game->keys.right = 1;
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->keys.w = 0;
	else if (keycode == A_KEY)
		game->keys.a = 0;
	else if (keycode == S_KEY)
		game->keys.s = 0;
	else if (keycode == D_KEY)
		game->keys.d = 0;
	else if (keycode == LEFT_KEY)
		game->keys.left = 0;
	else if (keycode == RIGHT_KEY)
		game->keys.right = 0;
	else if (keycode == ESC_KEY)
		game->keys.esc = 0;
	return (0);
}

int	process_active_keys(t_game *game)
{
	if (game->keys.esc)
		safe_exit(game, 0);
	if (game->keys.w)
		move_player_forward(game);
	if (game->keys.s)
		move_player_backward(game);
	if (game->keys.a)
		move_player_left(game);
	if (game->keys.d)
		move_player_right(game);
	if (game->keys.left)
		rotate_player(game, ROT_SPEED);
	if (game->keys.right)
		rotate_player(game, -ROT_SPEED);
	return (0);
}

int	handle_mouse_motion(int x, int y, t_game *game)
{
	int		delta_x;
	double	rotation_angle;

	if (!game->mouse.initialized)
	{
		game->mouse.last_x = x;
		game->mouse.initialized = 1;
		return (0);
	}
	delta_x = x - game->mouse.last_x;
	rotation_angle = delta_x * MOUSE_SENSITIVITY;
	rotate_player(game, -rotation_angle);
	game->mouse.last_x = x;
	game->mouse.x = x;
	game->mouse.y = y;
	return (0);
}
