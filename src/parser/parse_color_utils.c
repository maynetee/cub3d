/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:30:00 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:13:02 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

int	validate_comma_format(char *rest, t_config *cfg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (rest[i])
	{
		if (rest[i] == ',')
		{
			if (i == 0 || rest[i + 1] == ',' || rest[i + 1] == '\0')
				return (print_error_and_exit("Invalid color format", cfg));
			count++;
		}
		i++;
	}
	if (count != 2)
		return (print_error_and_exit("Invalid color format", cfg));
	return (0);
}

int	parse_component(char *s, int *out, t_config *cfg)
{
	char	*trim;
	int		val;

	trim = ft_strtrim(s, " \t");
	if (!trim)
		return (print_error_and_exit("Malloc failed", cfg));
	if (validate_numeric_string(trim, cfg))
		return (1);
	val = ft_atoi(trim);
	free(trim);
	if (val < 0 || val > 255)
		return (print_error_and_exit("Color out of range", cfg));
	*out = val;
	return (0);
}

int	parse_color_components(char **p, t_color *dst, t_config *cfg)
{
	int	r;
	int	g;
	int	b;

	if (parse_component(p[0], &r, cfg) || parse_component(p[1], &g, cfg)
		|| parse_component(p[2], &b, cfg))
		return (-1);
	dst->r = r;
	dst->g = g;
	dst->b = b;
	return (0);
}

int	parse_color(char *rest, t_color *dst, t_config *cfg)
{
	char	**p;

	if (validate_comma_format(rest, cfg))
		return (-1);
	p = ft_split(rest, ',');
	if (!p)
		return (print_error_and_exit("Malloc failed", cfg));
	if (parse_color_components(p, dst, cfg))
	{
		free_string_array(p);
		return (-1);
	}
	free_string_array(p);
	return (0);
}
