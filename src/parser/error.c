/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:17:31 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:12:20 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <unistd.h>

static void	free_map(t_map *map)
{
	int	i;

	if (map == NULL || map->grid == NULL)
		return ;
	i = 0;
	while (i < map->height && map->grid[i] != NULL)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
}

static void	free_textures(t_config *cfg)
{
	if (cfg->north_texture != NULL)
	{
		free(cfg->north_texture);
		cfg->north_texture = NULL;
	}
	if (cfg->south_texture != NULL)
	{
		free(cfg->south_texture);
		cfg->south_texture = NULL;
	}
	if (cfg->west_texture != NULL)
	{
		free(cfg->west_texture);
		cfg->west_texture = NULL;
	}
	if (cfg->east_texture != NULL)
	{
		free(cfg->east_texture);
		cfg->east_texture = NULL;
	}
}

void	free_config(t_config *cfg)
{
	if (cfg == NULL)
		return ;
	free_textures(cfg);
	free_map(&cfg->map);
}

int	print_error_and_exit(char *msg, t_config *cfg)
{
	if (cfg != NULL)
		free_config(cfg);
	write(2, "Error\n", 6);
	while (*msg)
	{
		write(2, msg, 1);
		msg++;
	}
	write(2, "\n", 1);
	return (1);
}

int	print_texture_error(char *path, t_config *cfg)
{
	int		i;

	if (cfg != NULL)
		free_config(cfg);
	write(2, "Error\n", 6);
	write(2, "Cannot open texture: ", 21);
	i = 0;
	while (path[i])
	{
		write(2, &path[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (1);
}
