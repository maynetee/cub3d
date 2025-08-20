/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_enclosure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:17:50 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:12:49 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int	validate_open_space(t_config *cfg, int i, int j)
{
	if (i == 0 || j == 0 || i == cfg->map.height - 1 || j == cfg->map.width - 1)
		return (print_error_and_exit("Map not closed", cfg));
	if (cfg->map.grid[i - 1][j] == ' ' || cfg->map.grid[i + 1][j] == ' '
		|| cfg->map.grid[i][j - 1] == ' ' || cfg->map.grid[i][j + 1] == ' ')
		return (print_error_and_exit("Map not closed", cfg));
	return (0);
}

static int	check_outer_walls(t_config *cfg)
{
	int	i;
	int	j;

	j = 0;
	while (j < cfg->map.width)
	{
		if (cfg->map.grid[0][j] != '1' || cfg->map.grid[cfg->map.height
			- 1][j] != '1')
			return (print_error_and_exit("Map not closed", cfg));
		j++;
	}
	i = 0;
	while (i < cfg->map.height)
	{
		if (cfg->map.grid[i][0] != '1' || cfg->map.grid[i][cfg->map.width
			- 1] != '1')
			return (print_error_and_exit("Map not closed", cfg));
		i++;
	}
	return (0);
}

static int	validate_row_spaces(t_config *cfg, int i)
{
	int		j;
	char	c;

	j = 0;
	while (j < cfg->map.width)
	{
		c = cfg->map.grid[i][j];
		if (c == '0')
		{
			if (validate_open_space(cfg, i, j))
				return (1);
		}
		else if (c == ' ')
		{
			if (validate_space_enclosure(cfg, i, j))
				return (1);
		}
		j++;
	}
	return (0);
}

static int	validate_inner_spaces(t_config *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->map.height)
	{
		if (validate_row_spaces(cfg, i))
			return (1);
		i++;
	}
	return (0);
}

int	validate_enclosure(t_config *cfg)
{
	if (check_outer_walls(cfg))
		return (1);
	if (validate_inner_spaces(cfg))
		return (1);
	return (flood_fill_check(cfg));
}
