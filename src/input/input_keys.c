#include "../../include/cube3d.h"

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		return (handle_exit_key(keycode, game));
	if (keycode == W_KEY || keycode == A_KEY
		|| keycode == S_KEY || keycode == D_KEY)
		return (process_movement_keys(keycode, game));
	if (keycode == LEFT_KEY || keycode == RIGHT_KEY)
		return (process_rotation_keys(keycode, game));
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	(void)keycode;
	(void)game;
	return (0);
}

int	process_movement_keys(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		return (move_player_forward(game));
	else if (keycode == S_KEY)
		return (move_player_backward(game));
	else if (keycode == A_KEY)
		return (move_player_left(game));
	else if (keycode == D_KEY)
		return (move_player_right(game));
	return (0);
}

int	process_rotation_keys(int keycode, t_game *game)
{
	if (keycode == LEFT_KEY)
		return (rotate_player(game, -ROT_SPEED));
	else if (keycode == RIGHT_KEY)
		return (rotate_player(game, ROT_SPEED));
	return (0);
}

int	handle_exit_key(int keycode, t_game *game)
{
	(void)keycode;
	return (safe_exit(game, 0));
}
