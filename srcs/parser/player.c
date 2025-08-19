/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:18:09 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:13:57 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_player_direction(t_config *cfg)
{
	static const t_dir_map	dirs[4] = {{'N', 0.0, -1.0}, {'S', 0.0, 1.0}, {'W',
		-1.0, 0.0}, {'E', 1.0, 0.0}};
	int						i;

	i = 0;
	while (i < 4)
	{
		if (cfg->player.dir == dirs[i].letter)
		{
			cfg->player.dir_x = dirs[i].x;
			cfg->player.dir_y = dirs[i].y;
			return ;
		}
		i++;
	}
}
