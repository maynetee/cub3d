#include "../../include/cube3d.h"

void	cleanup_game_resources(t_game *game)
{
	if (!game)
		return ;
	cleanup_texture_data(game);
	cleanup_mlx_resources(game);
	cleanup_scene_data(&game->scene);
}

void	cleanup_scene_data(t_scene *scene)
{
	int	i;

	if (!scene)
		return ;
	if (scene->map)
	{
		i = 0;
		while (i < scene->map_height && scene->map[i])
		{
			free(scene->map[i]);
			i++;
		}
		free(scene->map);
		scene->map = NULL;
	}
	i = 0;
	while (i < 4)
	{
		if (scene->texture_paths[i])
		{
			free(scene->texture_paths[i]);
			scene->texture_paths[i] = NULL;
		}
		i++;
	}
}

void	cleanup_texture_data(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < 4)
	{
		free_texture_resources(&game->textures[i]);
		i++;
	}
}

void	cleanup_mlx_resources(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	if (game->img)
	{
		mlx_destroy_image(game->mlx, game->img);
		game->img = NULL;
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
}

int	safe_exit(t_game *game, int exit_code)
{
	cleanup_game_resources(game);
	exit(exit_code);
}
