/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bergun <bergun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:13:33 by bergun            #+#    #+#             */
/*   Updated: 2024/06/18 20:08:36 by bergun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	array_count(char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!i)
			{
				count++;
				i = 1;
			}
		}
		else
			i = 0;
		s++;
	}
	return (count);
}

static int	array_len(char *s, char c)
{
	int	i;

	i = 0;
	while (*s && (*s != c))
	{
		i++;
		s++;
	}
	return (i);
}

static void	free_split(char **map, int i)
{
	while (i--)
		free(map[i]);
}

char	**ft_split(char const *s, char c)
{
	char	**map;
	int		i;

	if (!s)
		return (0);
	i = 0;
	map = ft_calloc((array_count((char *)s, c) + 1), sizeof(char *));
	if (!map)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			map[i] = ft_substr(s, 0, array_len((char *)s, c));
			if (!map[i++])
				return (free_split(map, i - 1), free(map), NULL);
			s += array_len((char *)s, c);
		}
		else
			s++;
	}
	map[i] = 0;
	return (map);
}
