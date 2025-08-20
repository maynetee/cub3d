/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:00:00 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/19 21:00:00 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int	check_file_extension(char *filename, char *extension)
{
	int	lf;
	int	le;

	lf = ft_strlen(filename);
	le = ft_strlen(extension);
	if (lf < le)
		return (0);
	return (ft_strncmp(filename + lf - le, extension, le) == 0);
}

int	check_texture_accessibility(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	validate_scene_elements(t_scene *scene)
{
	if (!scene->texture_paths[NO_TEX] || !scene->texture_paths[SO_TEX]
		|| !scene->texture_paths[WE_TEX] || !scene->texture_paths[EA_TEX])
		return (print_error("Error\nMissing texture path"), 0);
	if (scene->floor_color.r < 0 || scene->floor_color.r > 255
		|| scene->floor_color.g < 0 || scene->floor_color.g > 255
		|| scene->floor_color.b < 0 || scene->floor_color.b > 255)
		return (print_error("Error\nMissing or invalid floor color"), 0);
	if (scene->ceiling_color.r < 0 || scene->ceiling_color.r > 255
		|| scene->ceiling_color.g < 0 || scene->ceiling_color.g > 255
		|| scene->ceiling_color.b < 0 || scene->ceiling_color.b > 255)
		return (print_error("Error\nMissing or invalid ceiling color"), 0);
	scene->floor_color.hex = create_color_hex(scene->floor_color.r,
			scene->floor_color.g, scene->floor_color.b);
	scene->ceiling_color.hex = create_color_hex(scene->ceiling_color.r,
			scene->ceiling_color.g, scene->ceiling_color.b);
	return (1);
}
