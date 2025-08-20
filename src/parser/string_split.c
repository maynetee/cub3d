/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:00:00 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:14:01 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

static char	**create_tokens_array(char *trim, size_t *pos)
{
	char	**tab;

	tab = malloc(sizeof(char *) * 4);
	if (!tab)
		return (NULL);
	tab[0] = extract_first_token(trim, pos);
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}

static int	set_value_token(char **tab, char *trim, size_t start, size_t end)
{
	tab[1] = extract_value_token(trim, start, end);
	if (end > start && !tab[1])
	{
		cleanup_tab(tab, 1);
		return (0);
	}
	return (1);
}

static int	set_remainder_token(char **tab, char *trim, size_t pos)
{
	if (trim[pos])
	{
		tab[2] = ft_strtrim(trim + pos, " \t\r\n\v\f");
		if (!tab[2])
		{
			cleanup_tab(tab, 2);
			return (0);
		}
	}
	else
		tab[2] = NULL;
	tab[3] = NULL;
	return (1);
}

char	**split_identifier(char *trim)
{
	char	**tab;
	size_t	pos;
	size_t	start;
	size_t	end;

	tab = create_tokens_array(trim, &pos);
	if (!tab)
		return (NULL);
	while (trim[pos] && ft_isspace((unsigned char)trim[pos]))
		pos++;
	start = pos;
	end = find_value_end(trim, start);
	if (!set_value_token(tab, trim, start, end))
		return (NULL);
	pos = end;
	while (trim[pos] && ft_isspace((unsigned char)trim[pos]))
		pos++;
	if (!set_remainder_token(tab, trim, pos))
		return (NULL);
	return (tab);
}
