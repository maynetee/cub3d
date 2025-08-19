/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bergun <bergun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:41:15 by bergun            #+#    #+#             */
/*   Updated: 2024/05/22 18:50:28 by bergun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (*little == 0)
		return ((char *)big);
	if (len)
	{
		while (big[i] && i < len)
		{
			j = 0;
			while (big[i + j] == little[j] && i + j < len)
			{
				j++;
				if (!little[j])
					return ((char *)&big[i]);
			}
			i++;
		}
	}
	return (0);
}
