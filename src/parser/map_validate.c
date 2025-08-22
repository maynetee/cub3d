/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:17:55 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:12:58 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	process_player_char(t_config *cfg, char c, int i, int j)
{
	if (cfg->player_set)
		return (print_error_and_exit("Multiple player", cfg));
	cfg->player.dir = c;
	cfg->player.x = j + 0.5;
	cfg->player.y = i + 0.5;
	cfg->player_set = 1;
	cfg->map.grid[i][j] = '0';
	return (0);
}

static int	validate_cell(t_config *cfg, int i, int j)
{
	char	c;

	c = cfg->map.grid[i][j];
	if (is_player_char(c))
		return (process_player_char(cfg, c, i, j));
	if (c != '0' && c != '1' && c != ' ')
		return (print_error_and_exit("Invalid map character", cfg));
	return (0);
}

int	validate_map_chars_and_player(t_config *cfg)
{
	int	i;
	int	j;

	if (cfg->map.invalid_char)
		return (print_error_and_exit("Invalid map character", cfg));
	i = 0;
	while (i < cfg->map.height)
	{
		j = 0;
		while (j < cfg->map.width)
		{
			if (validate_cell(cfg, i, j))
				return (1);
			j++;
		}
		i++;
	}
	if (cfg->player_set == 0)
		return (print_error_and_exit("Missing player start", cfg));
	cfg_set_player_direction(cfg);
	return (0);
}

int	validate_space_enclosure(t_config *cfg, int i, int j)
{
	if (i == 0 || j == 0 || i == cfg->map.height - 1 || j == cfg->map.width - 1)
		return (0);
	return (0);
}
