/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bergun <bergun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:25:00 by bergun            #+#    #+#             */
/*   Updated: 2025/01/18 16:25:00 by bergun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"

int	init_mlx_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error("Error\nMLX initialization failed"), 0);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (handle_mlx_error(game));
	if (!init_mlx_image(game))
		return (0);
	return (1);
}

int	init_mlx_image(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)
		return (handle_mlx_error(game));
	game->img_data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->img_data)
		return (handle_mlx_error(game));
	return (1);
}

int	setup_mlx_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	return (1);
}

int	close_window(t_game *game)
{
	return (safe_exit(game, 0));
}

int	handle_mlx_error(t_game *game)
{
	print_error("Error\nMLX operation failed");
	cleanup_mlx_resources(game);
	return (0);
}
