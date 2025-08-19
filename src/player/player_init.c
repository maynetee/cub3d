#include "../../include/cube3d.h"

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
	int		i;
	int		j;
	char	direction;

	i = 0;
	while (i < scene->map_height)
	{
		j = 0;
		while (j < scene->map_width && scene->map[i][j])
		{
			direction = scene->map[i][j];
			if (direction == 'N' || direction == 'S'
				|| direction == 'E' || direction == 'W')
			{
				player->x = j + 0.5;
				player->y = i + 0.5;
				set_player_direction(player, direction);
				scene->map[i][j] = '0';
				return (1);
			}
			j++;
		}
		i++;
	}
	return (print_error("Error\nNo player spawn found"), 0);
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
