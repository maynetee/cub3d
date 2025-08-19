/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:17:45 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:12:41 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

static int	allocate_grid_rows(t_map *m, char **tmp, int h, t_config *cfg)
{
	int	i;

	i = 0;
	while (i < h)
	{
		m->grid[i] = alloc_padded_row(tmp[i], m->width);
		free(tmp[i]);
		if (m->grid[i] == NULL)
		{
			cleanup_partial(m, tmp, h, i);
			return (print_error_and_exit("Malloc failed", cfg));
		}
		i++;
	}
	return (0);
}

static int	free_tmp_and_error(char **tmp, int h, char *msg, t_config *cfg)
{
	int	i;

	i = 0;
	while (i < h)
	{
		free(tmp[i]);
		i++;
	}
	return (print_error_and_exit(msg, cfg));
}

static int	init_grid(t_map *m, int h)
{
	m->grid = ft_calloc(h, sizeof(char *));
	if (m->grid == NULL)
		return (0);
	return (1);
}

int	create_padded_grid(t_map *m, char **tmp, int h, t_config *cfg)
{
	int	w;

	w = max_width(tmp, h);
	if (w > MAX_MAP_COLS)
		return (free_tmp_and_error(tmp, h, "Map too wide", cfg));
	if (!init_grid(m, h))
		return (free_tmp_and_error(tmp, h, "Malloc failed", cfg));
	m->width = w;
	m->height = h;
	return (allocate_grid_rows(m, tmp, h, cfg));
}
