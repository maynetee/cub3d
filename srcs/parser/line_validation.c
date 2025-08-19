/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:15:00 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:12:36 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

static int	is_element_prefix(const char *str)
{
	if ((str[0] == 'N' && str[1] == 'O') || (str[0] == 'S' && str[1] == 'O')
		|| (str[0] == 'W' && str[1] == 'E') || (str[0] == 'E' && str[1] == 'A'))
		return (1);
	return (0);
}

static int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

static int	process_invalid_char(int has_map_char, int *invalid)
{
	if (has_map_char)
	{
		if (invalid)
			*invalid = 1;
		return (1);
	}
	return (0);
}

static int	check_map_chars(const char *l, size_t start, int *invalid)
{
	size_t	i;
	int		has_map_char;

	i = start;
	has_map_char = 0;
	while (l[i])
	{
		if (is_valid_map_char(l[i]))
			has_map_char = 1;
		else if (!ft_isspace((unsigned char)l[i]))
		{
			if (!process_invalid_char(has_map_char, invalid))
				return (0);
		}
		i++;
	}
	return (has_map_char);
}

int	is_map_line(const char *l, int *invalid)
{
	size_t	i;

	i = 0;
	while (l[i] && ft_isspace((unsigned char)l[i]))
		i++;
	if (!l[i])
		return (0);
	if (is_element_prefix(l + i))
		return (0);
	return (check_map_chars(l, i, invalid));
}
