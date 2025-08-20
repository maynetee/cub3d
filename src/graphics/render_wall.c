/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:54:45 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/20 22:12:49 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_walls(t_game *game, t_ray *ray, int x)
{
	int	texture_index;

	determine_wall_texture(ray, &texture_index);
	draw_wall_stripe(game, ray, x, texture_index);
	draw_floor_ceiling(game, x, ray);
}

static int	apply_shading(int color, int side)
{
	if (side == 1)
		return (color / 2);
	return (color);
}

static void	render_texture_line(t_game *game, t_ray *ray, int x, t_texture *tex)
{
	int		*buffer;
	int		y;
	int		tex_x;
	int		tex_y;

	buffer = (int *)game->img_data;
	calculate_texture_coords(ray, tex, &tex_x);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)((y - ray->draw_start) * tex->height / ray->line_height);
		buffer[y * WIN_WIDTH + x] = apply_shading(
				get_texture_pixel(tex, tex_x, tex_y), ray->side);
		y++;
	}
}

void	draw_wall_stripe(t_game *game, t_ray *ray, int x, int texture_index)
{
	t_texture	*tex;

	tex = &game->textures[texture_index];
	render_texture_line(game, ray, x, tex);
}

void	calculate_texture_coords(t_ray *ray, t_texture *tex, int *tex_x)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = ray->dir_y * ray->perp_wall_dist;
	else
		wall_x = ray->dir_x * ray->perp_wall_dist;
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		*tex_x = tex->width - *tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		*tex_x = tex->width - *tex_x - 1;
}
