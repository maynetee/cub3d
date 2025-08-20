/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:18:01 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:13:41 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

int	process_line_and_check_map(char *line, t_config *cfg, int fd)
{
	if (is_map_line(line, &cfg->map.invalid_char))
	{
		if (!all_elements_set(cfg))
			return (free(line), check_missing_elements(cfg));
		if (collect_map_lines(fd, line, &cfg->map, cfg))
			return (1);
		return (2);
	}
	if (parse_element_line(line, cfg))
		return (free(line), 1);
	return (0);
}
