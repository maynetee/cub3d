/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:05:00 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/20 22:12:49 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_floor_ceiling(t_game *game, int x, t_ray *ray)
{
	int	*buffer;
	int	y;

	buffer = (int *)game->img_data;
	y = 0;
	while (y < ray->draw_start)
	{
		buffer[y * WIN_WIDTH + x] = game->scene.ceiling_color.hex;
		y++;
	}
	y = ray->draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		buffer[y * WIN_WIDTH + x] = game->scene.floor_color.hex;
		y++;
	}
}

int	get_texture_pixel(t_texture *tex, int x, int y)
{
	int	*buffer;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	buffer = (int *)tex->data;
	return (buffer[y * tex->width + x]);
}
