/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:58:37 by fguryel           #+#    #+#             */
/*   Updated: 2024/11/03 16:37:19 by fguryel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_intlen(int n)
{
	unsigned int	i;
	unsigned int	num;

	i = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	num = n;
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

static unsigned int	ft_putnbr(int n, char *new_str, unsigned int i)
{
	if (n == -2147483648)
	{
		new_str[i++] = '-';
		new_str[i++] = '2';
		n = 147483648;
	}
	if (n < 0)
	{
		new_str[i++] = '-';
		n *= -1;
	}
	if (n > 9)
	{
		i = ft_putnbr(n / 10, new_str, i);
	}
	new_str[i++] = (n % 10) + '0';
	return (i);
}

char	*ft_itoa(int n)
{
	char			*new_str;
	unsigned int	len;
	unsigned int	i;

	len = ft_intlen(n);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	if (n == 0)
	{
		new_str[0] = '0';
		new_str[1] = '\0';
		return (new_str);
	}
	i = ft_putnbr(n, new_str, i);
	new_str[i] = '\0';
	return (new_str);
}
