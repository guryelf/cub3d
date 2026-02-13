/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:50:13 by fguryel           #+#    #+#             */
/*   Updated: 2024/11/03 16:43:25 by fguryel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*val;

	val = NULL;
	while (*s)
	{
		if (*s == (char)c)
			val = (char *)s;
		s++;
	}
	if ((char)c == 0)
		return ((char *)s);
	return (val);
}
