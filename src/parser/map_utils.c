/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:17:52 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/22 12:36:51 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

static char	*filter_spaces(char *src)
{
	char	*filtered;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(src);
	filtered = malloc(len + 1);
	if (!filtered)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (src[i] != ' ')
		{
			filtered[j] = src[i];
			j++;
		}
		i++;
	}
	filtered[j] = '\0';
	return (filtered);
}

static char	*pad_row(char *filtered, int width, int len)
{
	char	*dst;
	int		i;

	dst = malloc(width + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < width)
	{
		if (i < len)
			dst[i] = filtered[i];
		else
			dst[i] = ' ';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*alloc_padded_row(char *src, int width)
{
	char	*filtered;
	char	*dst;
	int		len;

	filtered = filter_spaces(src);
	if (!filtered)
		return (NULL);
	len = ft_strlen(filtered);
	dst = pad_row(filtered, width, len);
	free(filtered);
	return (dst);
}

int	max_width(char **tmp, int h)
{
	char	*filtered;
	int		i;
	int		w;
	int		len;

	w = 0;
	i = 0;
	while (i < h)
	{
		filtered = filter_spaces(tmp[i]);
		if (!filtered)
			return (0);
		len = ft_strlen(filtered);
		if (len > w)
			w = len;
		free(filtered);
		i++;
	}
	return (w);
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
