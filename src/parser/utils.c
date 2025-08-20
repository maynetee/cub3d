/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:18:13 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:14:15 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	all_elements_set(t_config *c)
{
	return (c->north_texture && c->south_texture && c->west_texture
		&& c->east_texture && c->floor_set && c->ceiling_set);
}

int	check_missing_elements(t_config *c)
{
	if (!c->north_texture)
		return (print_error_and_exit("Missing north texture", c));
	if (!c->south_texture)
		return (print_error_and_exit("Missing south texture", c));
	if (!c->west_texture)
		return (print_error_and_exit("Missing west texture", c));
	if (!c->east_texture)
		return (print_error_and_exit("Missing east texture", c));
	if (!c->floor_set)
		return (print_error_and_exit("Missing floor color", c));
	if (!c->ceiling_set)
		return (print_error_and_exit("Missing ceiling color", c));
	return (0);
}

void	strip_newline(char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while (len && (s[len - 1] == '\n' || s[len - 1] == '\r'))
	{
		s[len - 1] = '\0';
		len--;
	}
}

int	validate_numeric_string(char *trim, t_config *cfg)
{
	size_t	i;

	if (trim[0] == '\0')
	{
		free(trim);
		return (print_error_and_exit("Color not numeric", cfg));
	}
	i = 0;
	while (trim[i])
	{
		if (!ft_isdigit((unsigned char)trim[i]))
		{
			free(trim);
			return (print_error_and_exit("Color not numeric", cfg));
		}
		i++;
	}
	return (0);
}
