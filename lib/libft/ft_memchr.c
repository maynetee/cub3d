/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bergun <bergun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:15:02 by bergun            #+#    #+#             */
/*   Updated: 2024/05/22 18:53:06 by bergun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*lookup;
	size_t			i;

	i = 0;
	c = (unsigned char)c;
	lookup = (unsigned char *)s;
	while (i < n)
	{
		if (lookup[i] == c)
			return (lookup + i);
		i++;
	}
	return (0);
}
