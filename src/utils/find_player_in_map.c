/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player_in_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:55:01 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/19 20:55:04 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_player_position(int *x, int *y, int j, int i)
{
	if (x)
		*x = j;
	if (y)
		*y = i;
}

int	find_player_in_map(t_scene *scene, int *x, int *y, char *dir)
{
	int	i;
	int	j;

	if (!scene || !scene->map)
		return (0);
	i = 0;
	while (i < scene->map_height)
	{
		j = 0;
		while (j < scene->map_width && scene->map[i][j])
		{
			if (is_player_char(scene->map[i][j]))
			{
				set_player_position(x, y, j, i);
				if (dir)
					*dir = scene->map[i][j];
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
