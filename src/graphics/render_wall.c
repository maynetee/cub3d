#include "../../include/cube3d.h"

void	render_walls(t_game *game, t_ray *ray, int x)
{
	int	texture_index;

	determine_wall_texture(ray, &texture_index);
	draw_wall_stripe(game, ray, x);
	draw_floor_ceiling(game, x, ray);
}

void	draw_wall_stripe(t_game *game, t_ray *ray, int x)
{
	int	*buffer;
	int	y;
	int	color;

	buffer = (int *)game->img_data;
	y = ray->draw_start;
	color = 0xFF0000;
	if (ray->side == 1)
		color = color / 2;
	while (y < ray->draw_end)
	{
		buffer[y * WIN_WIDTH + x] = color;
		y++;
	}
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
