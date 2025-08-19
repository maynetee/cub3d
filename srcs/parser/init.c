/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:17:39 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:34:22 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int	parse_and_fill_config(const char *path, t_config *cfg)
{
	ft_bzero(cfg, sizeof(t_config));
	if (parse_cub_file((char *)path, cfg) != 0)
		return (1);
	return (0);
}
