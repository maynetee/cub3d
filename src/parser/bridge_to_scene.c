/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_to_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:52:39 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/19 20:52:40 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "libft.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>

static void	set_colors_hex(t_scene *scene)
{
	scene->floor_color.hex = create_color_hex(scene->floor_color.r,
			scene->floor_color.g, scene->floor_color.b);
	scene->ceiling_color.hex = create_color_hex(scene->ceiling_color.r,
			scene->ceiling_color.g, scene->ceiling_color.b);
}

static void	copy_textures_to_scene(t_scene *scene, t_config *cfg)
{
	scene->texture_paths[NO_TEX] = cfg->north_texture;
	scene->texture_paths[SO_TEX] = cfg->south_texture;
	scene->texture_paths[WE_TEX] = cfg->west_texture;
	scene->texture_paths[EA_TEX] = cfg->east_texture;
}

static void	copy_colors_to_scene(t_scene *scene, t_config *cfg)
{
	scene->floor_color.r = cfg->floor.r;
	scene->floor_color.g = cfg->floor.g;
	scene->floor_color.b = cfg->floor.b;
	scene->ceiling_color.r = cfg->ceiling.r;
	scene->ceiling_color.g = cfg->ceiling.g;
	scene->ceiling_color.b = cfg->ceiling.b;
}

static void	set_player_on_map(t_scene *scene, t_config *cfg)
{
	int	px;
	int	py;

	if (cfg->player_set)
	{
		px = (int)cfg->player.x;
		py = (int)cfg->player.y;
		if (py >= 0 && py < scene->map_height && px >= 0
			&& px < scene->map_width)
			scene->map[py][px] = cfg->player.dir;
	}
}

int	parse_scene_file(char *filename, t_scene *scene)
{
	t_config	cfg;

	ft_bzero(scene, sizeof(*scene));
	if (parse_and_fill_config(filename, &cfg) != 0)
		return (0);
	scene->map = cfg.map.grid;
	scene->map_width = cfg.map.width;
	scene->map_height = cfg.map.height;
	copy_textures_to_scene(scene, &cfg);
	copy_colors_to_scene(scene, &cfg);
	set_player_on_map(scene, &cfg);
	set_colors_hex(scene);
	scene->elements_found = 1;
	return (1);
}
