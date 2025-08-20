/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 23:20:58 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/20 22:12:49 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_error(char *message)
{
	if (message)
		ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
}

void	print_usage(void)
{
	ft_putstr_fd("Usage: ./cub3d <scene_file.cub>\n", 1);
	ft_putstr_fd("Scene file must contain:\n", 1);
	ft_putstr_fd("  - NO, SO, WE, EA texture paths\n", 1);
	ft_putstr_fd("  - F and C floor/ceiling colors (R,G,B)\n", 1);
	ft_putstr_fd("  - Map with walls (1), empty spaces (0), ", 1);
	ft_putstr_fd("and player start (N/S/E/W)\n", 1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (s1 - s2);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup_safe(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (s[len - 1] == '\n')
		len--;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

int	create_color_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
