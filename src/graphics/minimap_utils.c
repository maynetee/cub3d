/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:30:00 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/20 12:30:00 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"

void	put_pixel_to_image(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel = game->img_data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)pixel = color;
}

int	is_wall_at_position(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_y >= game->scene.map_height)
		return (1);
	if (map_x >= (int)ft_strlen(game->scene.map[map_y]))
		return (1);
	return (game->scene.map[map_y][map_x] == '1');
}

static void	draw_player_dot(t_game *game, int center[2])
{
	int	x;
	int	y;

	y = -3;
	while (y <= 3)
	{
		x = -3;
		while (x <= 3)
		{
			if (x * x + y * y <= 9)
				put_pixel_to_image(game, center[0] + x, center[1] + y,
					0xFF0000);
			x++;
		}
		y++;
	}
}

void	draw_minimap_player(t_game *game)
{
	int	center[2];

	center[0] = WIN_WIDTH - MINIMAP_SIZE - MINIMAP_OFFSET + MINIMAP_SIZE / 2;
	center[1] = MINIMAP_OFFSET + MINIMAP_SIZE / 2;
	draw_player_dot(game, center);
	put_pixel_to_image(game, center[0] + (int)(game->player.dir_x * 8),
		center[1] + (int)(game->player.dir_y * 8), 0xFF0000);
}
