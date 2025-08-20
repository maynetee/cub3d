/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 23:23:00 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/20 22:12:49 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (!validate_arguments(argc, argv))
		return (1);
	ft_memset(&game, 0, sizeof(t_game));
	game.mouse.initialized = 0;
	if (!initialize_game(&game, argv[1]))
	{
		safe_exit(&game, 1);
		return (1);
	}
	run_game_loop(&game);
	safe_exit(&game, 0);
	return (0);
}

int	initialize_game(t_game *game, char *scene_file)
{
	if (!parse_scene_file(scene_file, &game->scene))
		return (0);
	if (!validate_scene_elements(&game->scene))
		return (0);
	if (!validate_player_spawn(&game->scene))
		return (0);
	if (!setup_game_components(game))
		return (0);
	return (1);
}

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error("Error\nWrong number of arguments");
		print_usage();
		return (0);
	}
	if (!argv[1])
	{
		print_error("Error\nInvalid argument");
		return (0);
	}
	return (1);
}

int	setup_game_components(t_game *game)
{
	if (!init_mlx_window(game))
		return (0);
	if (!load_texture_files(game))
		return (0);
	if (!init_player_position(game))
		return (0);
	if (!setup_mlx_hooks(game))
		return (0);
	return (1);
}

void	run_game_loop(t_game *game)
{
	mlx_loop(game->mlx);
}
