/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 23:21:51 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/19 23:21:52 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"

void	render_frame(t_game *game)
{
	clear_frame_buffer(game);
	cast_rays_for_frame(game);
	render_minimap(game);
}

void	cast_rays_for_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray_parameters(&ray, &game->player, x);
		perform_dda_algorithm(&ray, game->scene.map);
		calculate_wall_distance(&ray, &game->player);
		calculate_wall_height(&ray);
		render_walls(game, &ray, x);
		x++;
	}
}

void	calculate_wall_height(t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	determine_wall_texture(t_ray *ray, int *texture_index)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			*texture_index = EA_TEX;
		else
			*texture_index = WE_TEX;
	}
	else
	{
		if (ray->dir_y > 0)
			*texture_index = SO_TEX;
		else
			*texture_index = NO_TEX;
	}
}

void	clear_frame_buffer(t_game *game)
{
	int	*buffer;
	int	i;

	buffer = (int *)game->img_data;
	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT / 2)
	{
		buffer[i] = game->scene.ceiling_color.hex;
		i++;
	}
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		buffer[i] = game->scene.floor_color.hex;
		i++;
	}
}
