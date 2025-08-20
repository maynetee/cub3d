/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 23:21:04 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/20 22:12:49 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*pad_line_with_spaces(char *line, int target_width)
{
	char	*padded;
	int		i;
	int		original_len;

	original_len = ft_strlen(line);
	padded = malloc(target_width + 1);
	if (!padded)
		return (NULL);
	i = 0;
	while (i < original_len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < target_width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[target_width] = '\0';
	return (padded);
}

int	is_surrounded_by_walls(t_scene *scene, int y, int x)
{
	if (y == 0 || y == scene->map_height - 1 || x == 0
		|| x >= (int)ft_strlen(scene->map[y]))
		return (0);
	if (y > 0 && (scene->map[y - 1][x] == ' '
		|| scene->map[y - 1][x] == '\0'))
		return (0);
	if (y < scene->map_height - 1
		&& (scene->map[y + 1][x] == ' ' || scene->map[y + 1][x] == '\0'))
		return (0);
	if (x > 0 && scene->map[y][x - 1] == ' ')
		return (0);
	if (scene->map[y][x + 1] == ' ' || scene->map[y][x + 1] == '\0')
		return (0);
	return (1);
}

int	is_valid_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	check_map_characters(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	while (i < scene->map_height)
	{
		j = 0;
		while (j < scene->map_width)
		{
			if (!is_valid_map_char(scene->map[i][j]))
				return (print_error("Error\nInvalid character in map"), 0);
			j++;
		}
		i++;
	}
	return (1);
}
