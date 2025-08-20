/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:51:54 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/19 20:51:57 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"

int	load_texture_files(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!load_single_texture(game, i, game->scene.texture_paths[i]))
			return (0);
		i++;
	}
	return (1);
}

int	load_single_texture(t_game *game, int index, char *path)
{
	t_texture	*tex;

	tex = &game->textures[index];
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
		return (print_error("Error\nFailed to load texture"), 0);
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line,
			&tex->endian);
	if (!tex->data)
		return (print_error("Error\nFailed to get texture data"), 0);
	if (!validate_texture_data(tex))
		return (0);
	return (1);
}

int	validate_texture_data(t_texture *texture)
{
	if (!texture->img || !texture->data)
		return (print_error("Error\nInvalid texture data"), 0);
	if (texture->width <= 0 || texture->height <= 0)
		return (print_error("Error\nInvalid texture dimensions"), 0);
	return (1);
}

int	free_texture_resources(t_game *game, t_texture *texture)
{
	if (!game || !texture)
		return (0);
	if (texture->img)
	{
		mlx_destroy_image(game->mlx, texture->img);
		texture->img = NULL;
	}
	texture->data = NULL;
	texture->width = 0;
	texture->height = 0;
	return (1);
}
