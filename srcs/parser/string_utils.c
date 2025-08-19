/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:18:16 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:14:11 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

int	only_whitespace(char *l)
{
	int	i;

	i = 0;
	while (l[i] && ft_isspace((unsigned char)l[i]))
		i++;
	return (l[i] == '\0');
}

int	abort_with(char *line, char ***tmp, char *msg, t_config *cfg)
{
	free(line);
	free_string_array(*tmp);
	return (print_error_and_exit(msg, cfg));
}

static char	*trim_line(char *line, t_config *cfg)
{
	char	*trim;

	trim = ft_strtrim(line, " \t\r\n\v\f");
	if (!trim)
		print_error_and_exit("Malloc failed", cfg);
	return (trim);
}

static char	**tokenize_line(char *trim, t_config *cfg)
{
	char	**tab;

	tab = split_identifier(trim);
	if (!tab)
		print_error_and_exit("Malloc failed", cfg);
	return (tab);
}

char	**prepare_tokens(char *line, t_config *cfg)
{
	char	*trim;
	char	**tab;

	trim = trim_line(line, cfg);
	if (!trim)
		return (NULL);
	tab = tokenize_line(trim, cfg);
	free(trim);
	return (tab);
}
