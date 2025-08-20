/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 23:22:45 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/19 23:22:46 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"

int	game_loop(t_game *game)
{
	update_game_state(game);
	render_game_frame(game);
	return (0);
}

void	update_game_state(t_game *game)
{
	process_active_keys(game);
}

void	render_game_frame(t_game *game)
{
	render_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	calculate_frame_time(void)
{
	static struct timeval	last_time;
	struct timeval			current_time;
	int						frame_time;

	gettimeofday(&current_time, NULL);
	frame_time = (current_time.tv_sec - last_time.tv_sec) * 1000000
		+ (current_time.tv_usec - last_time.tv_usec);
	last_time = current_time;
	return (frame_time);
}

void	limit_frame_rate(int frame_time)
{
	int	target_frame_time;

	target_frame_time = 16667;
	if (frame_time < target_frame_time)
		usleep(target_frame_time - frame_time);
}
