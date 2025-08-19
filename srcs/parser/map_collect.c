/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:17:47 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:12:45 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

static int	ensure_capacity(char *line, t_collect_data *data)
{
	if (++(*(data->h)) > MAX_MAP_LINES)
		return (abort_with(line, data->tmp, "Map too tall", data->cfg));
	if (*(data->h) > *(data->cap))
	{
		*(data->cap) *= 2;
		*(data->tmp) = ft_realloc_tab(*(data->tmp), *(data->cap));
		if (!*(data->tmp))
			return (abort_with(line, data->tmp, "Malloc failed", data->cfg));
	}
	return (0);
}

static int	collect_lines_loop(int fd, t_collect_data *data)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		if (!is_map_line(line, &data->cfg->map.invalid_char))
		{
			if (only_whitespace(line))
				return (abort_with(line, data->tmp, "Empty line in map",
						data->cfg));
			return (abort_with(line, data->tmp, "Trailing data after map",
					data->cfg));
		}
		if (ensure_capacity(line, data))
			return (1);
		(*(data->tmp))[*(data->h) - 1] = line;
		line = get_next_line(fd);
	}
	return (0);
}

static int	shrink_tmp(char ***tmp, int *cap, int h, t_config *cfg)
{
	char	**new;

	if (*cap <= h)
		return (0);
	new = ft_realloc_tab(*tmp, h);
	if (!new)
	{
		free_string_array(*tmp);
		return (print_error_and_exit("Malloc failed", cfg));
	}
	*tmp = new;
	*cap = h;
	return (0);
}

static char	**init_tmp_array(char *first, t_config *cfg)
{
	char	**tmp;
	char	*dup;

	tmp = ft_realloc_tab(NULL, 16);
	if (!tmp)
	{
		free(first);
		print_error_and_exit("Malloc failed", cfg);
		return (NULL);
	}
	dup = ft_strdup(first);
	if (!dup)
	{
		free(first);
		free(tmp);
		print_error_and_exit("Malloc failed", cfg);
		return (NULL);
	}
	tmp[0] = dup;
	return (tmp);
}

int	collect_map_lines(int fd, char *first, t_map *m, t_config *cfg)
{
	char			**tmp;
	int				h;
	int				cap;
	t_collect_data	data;

	tmp = init_tmp_array(first, cfg);
	if (!tmp)
		return (1);
	h = 1;
	cap = 16;
	data = (t_collect_data){&tmp, &h, &cap, cfg};
	if (collect_lines_loop(fd, &data))
		return (1);
	if (shrink_tmp(&tmp, &cap, h, cfg))
		return (1);
	if (create_padded_grid(m, tmp, h, cfg))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
