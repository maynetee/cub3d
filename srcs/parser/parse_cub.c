/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:18:03 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:13:45 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int	has_cub_extension(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static int	parse_file_content(int fd, t_config *cfg)
{
	char	*line;
	int		result;

	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		result = process_line_and_check_map(line, cfg, fd);
		if (result == 1)
			return (1);
		if (result == 2)
		{
			free(line);
			line = NULL;
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

static int	finalize_config(t_config *cfg)
{
	if (!cfg->map.grid)
		return (print_error_and_exit("No map found", cfg));
	if (!cfg->floor_set)
		return (print_error_and_exit("Missing floor color", cfg));
	if (!cfg->ceiling_set)
		return (print_error_and_exit("Missing ceiling color", cfg));
	if (!cfg->north_texture)
		return (print_error_and_exit("Missing north texture", cfg));
	if (!cfg->south_texture)
		return (print_error_and_exit("Missing south texture", cfg));
	if (!cfg->west_texture)
		return (print_error_and_exit("Missing west texture", cfg));
	if (!cfg->east_texture)
		return (print_error_and_exit("Missing east texture", cfg));
	if (validate_map_chars_and_player(cfg) || validate_enclosure(cfg))
		return (1);
	return (0);
}

int	parse_cub_file(char *path, t_config *cfg)
{
	int	fd;

	if (!has_cub_extension(path))
		return (print_error_and_exit("Invalid map extension", cfg));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print_error_and_exit("Cannot open file", cfg));
	if (parse_file_content(fd, cfg))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (finalize_config(cfg));
}
