/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:17:58 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:13:37 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

int	parse_floor_line(char **tab, t_config *cfg)
{
	int	ret;

	if (cfg->floor_set)
		return (print_error_and_exit("Duplicate floor", cfg));
	if (!tab[1])
		return (print_error_and_exit("Missing floor color", cfg));
	if (tab[2])
		return (print_error_and_exit("Too many arguments", cfg));
	ret = parse_color(tab[1], &cfg->floor, cfg);
	if (ret == 0)
		cfg->floor_set = 1;
	return (ret);
}

int	parse_ceiling_line(char **tab, t_config *cfg)
{
	int	ret;

	if (cfg->ceiling_set)
		return (print_error_and_exit("Duplicate ceiling", cfg));
	if (!tab[1])
		return (print_error_and_exit("Missing ceiling color", cfg));
	if (tab[2])
		return (print_error_and_exit("Too many arguments", cfg));
	ret = parse_color(tab[1], &cfg->ceiling, cfg);
	if (ret == 0)
		cfg->ceiling_set = 1;
	return (ret);
}
