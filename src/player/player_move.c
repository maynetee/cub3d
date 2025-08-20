/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:51:21 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/19 20:51:22 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"

int	move_player_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (new_y >= 0 && new_y < game->scene.map_height && game->player.x >= 0
		&& game->player.x < game->scene.map_width
		&& game->scene.map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->player.y >= 0 && game->player.y < game->scene.map_height
		&& new_x >= 0 && new_x < game->scene.map_width
		&& game->scene.map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	return (0);
}

int	move_player_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (new_y >= 0 && new_y < game->scene.map_height && game->player.x >= 0
		&& game->player.x < game->scene.map_width
		&& game->scene.map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->player.y >= 0 && game->player.y < game->scene.map_height
		&& new_x >= 0 && new_x < game->scene.map_width
		&& game->scene.map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	return (0);
}

int	move_player_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_y * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_x * MOVE_SPEED;
	if (new_y >= 0 && new_y < game->scene.map_height && game->player.x >= 0
		&& game->player.x < game->scene.map_width
		&& game->scene.map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->player.y >= 0 && game->player.y < game->scene.map_height
		&& new_x >= 0 && new_x < game->scene.map_width
		&& game->scene.map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	return (0);
}

int	move_player_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_y * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_x * MOVE_SPEED;
	if (new_y >= 0 && new_y < game->scene.map_height && game->player.x >= 0
		&& game->player.x < game->scene.map_width
		&& game->scene.map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->player.y >= 0 && game->player.y < game->scene.map_height
		&& new_x >= 0 && new_x < game->scene.map_width
		&& game->scene.map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	return (0);
}

int	rotate_player(t_game *game, double rotation_angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rotation_angle)
		- game->player.dir_y * sin(rotation_angle);
	game->player.dir_y = old_dir_x * sin(rotation_angle) + game->player.dir_y
		* cos(rotation_angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rotation_angle)
		- game->player.plane_y * sin(rotation_angle);
	game->player.plane_y = old_plane_x * sin(rotation_angle)
		+ game->player.plane_y * cos(rotation_angle);
	return (0);
}
