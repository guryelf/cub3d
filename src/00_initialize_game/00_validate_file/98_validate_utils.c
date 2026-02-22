/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   98_validate_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:50:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/22 23:49:18 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_lines(char **arr)
{
	int	count;

	count = 0;
	if (!arr)
		return (0);
	while (arr[count])
		count++;
	return (count);
}

int	count_words(const char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] && line[i] != '\n')
		{
			count++;
			while (line[i] && line[i] != ' ' && line[i] != '\n')
				i++;
		}
	}
	return (count);
}
