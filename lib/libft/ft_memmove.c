/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:29:42 by fguryel           #+#    #+#             */
/*   Updated: 2024/11/03 16:37:41 by fguryel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(int reverse, unsigned char *dest, unsigned char *src,
		size_t len)
{
	size_t	i;

	if (reverse == 0)
	{
		i = len;
		while (i > 0)
		{
			dest[i - 1] = src[i - 1];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			dest[i] = src[i];
			i++;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*source;
	unsigned char	*destination;

	if (dst == NULL && src == NULL)
		return (NULL);
	source = (unsigned char *)src;
	destination = (unsigned char *)dst;
	if (dst < src)
		ft_strcpy(1, destination, source, len);
	else
		ft_strcpy(0, destination, source, len);
	return (dst);
}
