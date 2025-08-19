/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:17:52 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:12:54 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

char	*alloc_padded_row(char *src, int width)
{
	char	*dst;
	int		i;
	int		len;

	len = ft_strlen(src);
	dst = malloc(width + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < width)
	{
		if (i < len)
			dst[i] = src[i];
		else
			dst[i] = ' ';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	max_width(char **tmp, int h)
{
	int	i;
	int	w;
	int	len;

	w = 0;
	i = 0;
	while (i < h)
	{
		len = ft_strlen(tmp[i]);
		if (len > w)
			w = len;
		i++;
	}
	return (w);
}

void	cleanup_partial(t_map *m, char **tmp, int h, int i)
{
	int	j;

	j = i + 1;
	while (j < h)
	{
		free(tmp[j]);
		j++;
	}
	m->height = i;
	m->width = 0;
}

int	validate_space_enclosure(t_config *cfg, int i, int j)
{
	if (i > 0 && i < cfg->map.height - 1 && j > 0 && j < cfg->map.width - 1)
	{
		return (print_error_and_exit("Map not closed", cfg));
	}
	return (0);
}

int	flood_fill_check(t_config *cfg)
{
	int	*vis;
	int	res;

	vis = ft_calloc(cfg->map.height * cfg->map.width, sizeof(int));
	if (!vis)
		return (print_error_and_exit("Malloc failed", cfg));
	res = flood_fill(&cfg->map, vis, (int)cfg->player.y, (int)cfg->player.x);
	free(vis);
	if (res == -1)
		return (print_error_and_exit("Malloc failed", cfg));
	if (res)
		return (print_error_and_exit("Map not closed", cfg));
	return (0);
}
