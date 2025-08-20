/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 01:15:00 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/20 22:12:49 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_minimap(t_game *game)
{
	draw_minimap_background(game);
	draw_minimap_walls(game);
	draw_minimap_player(game);
}

void	draw_minimap_background(t_game *game)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;

	start_x = WIN_WIDTH - MINIMAP_SIZE - MINIMAP_OFFSET;
	start_y = MINIMAP_OFFSET;
	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			put_pixel_to_image(game, start_x + x, start_y + y, 0x404040);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_pixel(t_game *game, int x, int y, int start[2])
{
	int	map_x;
	int	map_y;

	map_x = (int)((game->player.x - MINIMAP_SIZE / MINIMAP_SCALE / 2)
			+ (x / MINIMAP_SCALE));
	map_y = (int)((game->player.y - MINIMAP_SIZE / MINIMAP_SCALE / 2)
			+ (y / MINIMAP_SCALE));
	if (is_wall_at_position(game, map_x, map_y))
		put_pixel_to_image(game, start[0] + x, start[1] + y, 0xFFFFFF);
}

void	draw_minimap_walls(t_game *game)
{
	int	x;
	int	y;
	int	start[2];

	start[0] = WIN_WIDTH - MINIMAP_SIZE - MINIMAP_OFFSET;
	start[1] = MINIMAP_OFFSET;
	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			draw_minimap_pixel(game, x, y, start);
			x++;
		}
		y++;
	}
}
