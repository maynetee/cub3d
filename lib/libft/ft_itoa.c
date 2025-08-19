/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bergun <bergun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 02:49:18 by bergun            #+#    #+#             */
/*   Updated: 2024/05/22 03:12:49 by bergun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	long int	nbr;
	int			count;

	nbr = n;
	count = 1;
	if (n < 0)
	{
		count++;
		nbr *= -1;
	}
	while (nbr >= 10)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	nbr;
	int			i;

	i = count_digits(n);
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (0);
	str[i--] = '\0';
	nbr = n;
	if (n < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (nbr >= 10)
	{
		str[i--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[i] = nbr + '0';
	return (str);
}
