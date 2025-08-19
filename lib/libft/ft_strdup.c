/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bergun <bergun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:22:10 by bergun            #+#    #+#             */
/*   Updated: 2024/05/22 19:24:56 by bergun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*r_string;

	i = 0;
	while (s[i])
		i++;
	r_string = malloc(sizeof(char) * (i + 1));
	if (r_string == NULL)
		return (0);
	i = -1;
	while (s[++i])
		r_string[i] = s[i];
	r_string[i] = '\0';
	return (r_string);
}
