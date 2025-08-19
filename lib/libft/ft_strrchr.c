/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bergun <bergun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:54:31 by bergun            #+#    #+#             */
/*   Updated: 2024/05/22 18:29:29 by bergun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	length;

	c = (unsigned char)c;
	length = ft_strlen(s);
	if (c == 0)
		return ((char *)s + length);
	while (length-- > 0)
		if (s[length] == c)
			return ((char *)s + length);
	return (0);
}
