/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bergun <bergun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:32:38 by bergun            #+#    #+#             */
/*   Updated: 2024/05/22 18:52:44 by bergun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*l1;
	unsigned char	*l2;
	size_t			i;

	l1 = (unsigned char *)s1;
	l2 = (unsigned char *)s2;
	i = -1;
	while (++i < n)
		if (l1[i] != l2[i])
			return (l1[i] - l2[i]);
	return (0);
}
