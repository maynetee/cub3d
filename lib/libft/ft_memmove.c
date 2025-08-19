/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bergun <bergun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:14:12 by bergun            #+#    #+#             */
/*   Updated: 2024/05/17 22:14:19 by bergun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest,	const void *src, size_t n)
{
	unsigned char	*dest_buffer;
	unsigned char	*src_buffer;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = -1;
	dest_buffer = (unsigned char *)dest;
	src_buffer = (unsigned char *)src;
	if (dest_buffer > src_buffer)
		while (n-- > 0)
			dest_buffer[n] = src_buffer[n];
	else
		while (++i < n)
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	return (dest);
}
