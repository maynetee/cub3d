/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:18:20 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:39:00 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (argc != 2)
		return (write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31), 1);
	if (parse_and_fill_config(argv[1], &cfg) != 0)
		return (1);
	///your code here
	free_config(&cfg);
	return (0);
}
