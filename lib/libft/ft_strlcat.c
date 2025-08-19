/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bergun <bergun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:25:05 by bergun            #+#    #+#             */
/*   Updated: 2024/05/22 18:28:41 by bergun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;

	if (siz == 0)
		return (ft_strlen(src));
	i = 0;
	while (dst[i] && i < siz)
		i++;
	j = -1;
	while (src[++j] && i + j + 1 < siz)
		dst[i + j] = src[j];
	if (i != siz)
		dst[i + j] = 0;
	return (i + ft_strlen(src));
}
