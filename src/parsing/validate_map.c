#include "../../include/cube3d.h"

int	validate_map_format(t_scene *scene)
{
	if (!scene->map || scene->map_height < 3)
		return (print_error("Error\nMap too small"), 0);
	if (!normalize_map_lines(scene))
		return (0);
	if (!check_map_characters(scene))
		return (0);
	if (!validate_player_position(scene))
		return (0);
	if (!validate_map_walls(scene))
		return (0);
	return (1);
}

int	validate_map_walls(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	while (i < scene->map_height)
	{
		j = 0;
		while (j < scene->map_width)
		{
			if (scene->map[i][j] == '0' || scene->map[i][j] == 'N' ||
				scene->map[i][j] == 'S' || scene->map[i][j] == 'E' ||
				scene->map[i][j] == 'W')
			{
				if (!is_surrounded_by_walls(scene, i, j))
					return (print_error("Error\nMap not enclosed by walls"), 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_player_position(t_scene *scene)
{
	int		player_x;
	int		player_y;
	char	player_dir;

	if (!find_player_in_map(scene, &player_x, &player_y, &player_dir))
		return (print_error("Error\nNo player found in map"), 0);
	return (1);
}

static int	check_player_at_position(t_scene *scene, int i, int j,
	int *player_count)
{
	if (scene->map[i][j] == 'N' || scene->map[i][j] == 'S'
		|| scene->map[i][j] == 'E' || scene->map[i][j] == 'W')
	{
		(*player_count)++;
		return (1);
	}
	return (0);
}

int	find_player_in_map(t_scene *scene, int *x, int *y, char *dir)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < scene->map_height && player_count <= 1)
	{
		j = 0;
		while (j < scene->map_width && player_count <= 1)
		{
			if (check_player_at_position(scene, i, j, &player_count))
			{
				*x = j;
				*y = i;
				*dir = scene->map[i][j];
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (print_error("Error\nInvalid number of players"), 0);
	return (1);
}
