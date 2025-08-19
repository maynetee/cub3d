/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bergun <bergun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:46:48 by bergun            #+#    #+#             */
/*   Updated: 2024/06/22 20:33:04 by bergun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clean_cache(char *cache)
{
	size_t	i;
	size_t	j;
	char	*next_cache;

	i = 0;
	while (cache && cache[i] && cache[i] != '\n')
		i++;
	if (!cache || !cache[i])
		return (free(cache), NULL);
	next_cache = ft_calloc((ft_strlen(cache) - i + 1), sizeof(char));
	if (!next_cache)
		return (NULL);
	i++;
	j = 0;
	while (cache[i])
		next_cache[j++] = cache[i++];
	next_cache[j] = 0;
	free(cache);
	return (next_cache);
}

static char	*read_next_line(char *cache)
{
	int		i;
	char	*next_line;

	i = 0;
	if (!cache || !cache[i])
		return (NULL);
	while (cache[i] && cache[i] != '\n')
		i++;
	next_line = ft_calloc((i + 2), sizeof(char));
	if (!next_line)
		return (NULL);
	i = 0;
	while (cache[i] && cache[i] != '\n')
	{
		next_line[i] = cache[i];
		i++;
	}
	if (cache[i] && cache[i] == '\n')
		next_line[i++] = '\n';
	next_line[i] = 0;
	return (next_line);
}

static char	*cache_buffer(int fd, char *cache)
{
	char	*temp;
	char	*next_line;
	int		bytes_read;

	if (!cache)
		cache = ft_calloc(1, sizeof(char));
	temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(cache, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(cache), free(temp), NULL);
		temp[bytes_read] = 0;
		next_line = ft_strjoin(cache, temp);
		free(cache);
		cache = next_line;
	}
	free(temp);
	return (cache);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	cache = cache_buffer(fd, cache);
	next_line = read_next_line(cache);
	cache = clean_cache(cache);
	return (next_line);
}
