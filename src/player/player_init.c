/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:51:04 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/20 22:12:49 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	init_player_position(t_game *game)
{
	if (!find_player_spawn(&game->scene, &game->player))
		return (0);
	calculate_initial_plane(&game->player);
	return (1);
}

void	set_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (direction == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (direction == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (direction == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

int	find_player_spawn(t_scene *scene, t_player *player)
{
	int		x;
	int		y;
	char	direction;

	if (!find_player_in_map(scene, &x, &y, &direction))
		return (print_error("Error\nNo player spawn found"), 0);
	player->x = x + 0.5;
	player->y = y + 0.5;
	set_player_direction(player, direction);
	scene->map[y][x] = '0';
	return (1);
}

void	calculate_initial_plane(t_player *player)
{
	player->plane_x = player->dir_y * 0.66;
	player->plane_y = -player->dir_x * 0.66;
}

int	validate_player_spawn(t_scene *scene)
{
	int		player_x;
	int		player_y;
	char	player_dir;

	return (find_player_in_map(scene, &player_x, &player_y, &player_dir));
}
