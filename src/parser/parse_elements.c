/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:18:07 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:13:49 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int	validate_texture_path(char *path, t_config *cfg)
{
	int	fd;
	int	len;

	len = ft_strlen(path);
	if (len <= 4 || ft_strncmp(path + len - 4, ".xpm", 4))
		return (print_error_and_exit("Texture must be .xpm", cfg));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print_texture_error(path, cfg));
	close(fd);
	return (0);
}

static int	set_texture(char **slot, char *path, t_config *cfg)
{
	if (*slot)
		return (print_error_and_exit("Duplicate texture", cfg));
	if (validate_texture_path(path, cfg))
		return (1);
	*slot = ft_strdup(path);
	if (!*slot)
		return (print_error_and_exit("Malloc failed", cfg));
	return (0);
}

static int	parse_texture_line(char **tab, t_config *cfg)
{
	char	**slot;

	slot = NULL;
	if (!tab[1])
		return (print_error_and_exit("Missing texture path", cfg));
	if (tab[2])
		return (print_error_and_exit("Too many arguments", cfg));
	if (!ft_strncmp(tab[0], "NO", 2))
		slot = &cfg->north_texture;
	else if (!ft_strncmp(tab[0], "SO", 2))
		slot = &cfg->south_texture;
	else if (!ft_strncmp(tab[0], "WE", 2))
		slot = &cfg->west_texture;
	else if (!ft_strncmp(tab[0], "EA", 2))
		slot = &cfg->east_texture;
	return (set_texture(slot, tab[1], cfg));
}

static int	parse_element_token(char **tab, t_config *cfg)
{
	if (!ft_strncmp(tab[0], "NO", 2) || !ft_strncmp(tab[0], "SO", 2)
		|| !ft_strncmp(tab[0], "WE", 2) || !ft_strncmp(tab[0], "EA", 2))
		return (parse_texture_line(tab, cfg));
	else if (tab[0][0] == 'F' && !tab[0][1])
		return (parse_floor_line(tab, cfg));
	else if (tab[0][0] == 'C' && !tab[0][1])
		return (parse_ceiling_line(tab, cfg));
	else
		return (print_error_and_exit("Invalid identifier", cfg));
}

int	parse_element_line(char *line, t_config *cfg)
{
	char	**tab;
	int		ret;

	tab = prepare_tokens(line, cfg);
	if (!tab)
		return (1);
	if (!tab[0] || !tab[0][0])
	{
		free_string_array(tab);
		return (0);
	}
	ret = parse_element_token(tab, cfg);
	free_string_array(tab);
	return (ret);
}
