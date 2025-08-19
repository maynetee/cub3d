/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bergun <bergun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:00:27 by bergun            #+#    #+#             */
/*   Updated: 2024/06/17 15:02:44 by bergun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*c;
	void	*ptr;

	if (!nmemb || !size)
	{
		c = malloc(0);
		if (c == NULL)
			return (0);
		*c = 0;
		return (c);
	}
	if (nmemb > SIZE_MAX / size)
		return (0);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (0);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
