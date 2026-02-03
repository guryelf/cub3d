/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:35:47 by fguryel           #+#    #+#             */
/*   Updated: 2024/10/11 17:44:13 by fguryel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c)
{
	if (!(c >= 48 && c <= 57))
	{
		return (0);
	}
	return (1);
}

static int	ft_isalpha(int c)
{
	if ((c < 65 || c > 90) && (c < 97 || c > 122))
	{
		return (0);
	}
	return (1);
}

int	ft_isalnum(int c)
{
	if ((ft_isdigit(c) == 0) && (ft_isalpha(c) == 0))
	{
		return (0);
	}
	return (1);
}
