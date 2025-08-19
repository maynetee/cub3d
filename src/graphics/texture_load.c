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
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (print_error("Error\nFailed to load texture"), 0);
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->size_line, &tex->endian);
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

int	convert_texture_data(t_texture *texture)
{
	(void)texture;
	return (1);
}

int	free_texture_resources(t_texture *texture)
{
	if (!texture)
		return (0);
	if (texture->img)
	{
		texture->img = NULL;
	}
	texture->data = NULL;
	texture->width = 0;
	texture->height = 0;
	return (1);
}
