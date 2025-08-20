/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:20:00 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:14:07 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

char	*extract_first_token(char *trim, size_t *pos)
{
	size_t	i;
	char	*tmp;
	char	*result;

	i = 0;
	while (trim[i] && !ft_isspace((unsigned char)trim[i]))
		i++;
	tmp = ft_substr(trim, 0, i);
	if (!tmp)
		return (NULL);
	result = ft_strtrim(tmp, " \t\r\n\v\f");
	free(tmp);
	*pos = i;
	return (result);
}

size_t	find_value_end(char *trim, size_t start)
{
	size_t	i;
	char	prev;

	i = start;
	prev = '\0';
	while (trim[i])
	{
		if (ft_isspace((unsigned char)trim[i]) && prev != ',')
			break ;
		if (!ft_isspace((unsigned char)trim[i]))
			prev = trim[i];
		i++;
	}
	return (i);
}

char	*extract_value_token(char *trim, size_t start, size_t end)
{
	char	*tmp;
	char	*result;

	if (end <= start)
		return (NULL);
	tmp = ft_substr(trim, start, end - start);
	if (!tmp)
		return (NULL);
	result = ft_strtrim(tmp, " \t\r\n\v\f");
	free(tmp);
	return (result);
}

void	cleanup_tab(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
