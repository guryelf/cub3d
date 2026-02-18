/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_validate_color_format.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:57:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/18 15:57:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int	skip_spaces_fc(const char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}

static int	read_digits(const char *line, int i, int *count)
{
	*count = 0;
	while (line[i] >= '0' && line[i] <= '9')
	{
		(*count)++;
		i++;
	}
	return (i);
}

static int	check_color_component(const char *line, int *i)
{
	int	digit_count;

	*i = skip_spaces_fc(line, *i);
	if (!(line[*i] >= '0' && line[*i] <= '9'))
		return (0);
	*i = read_digits(line, *i, &digit_count);
	if (digit_count < 1 || digit_count > 3)
		return (0);
	*i = skip_spaces_fc(line, *i);
	return (1);
}

int	validate_color_format(const char *line)
{
	int	i;
	int	comma;

	i = 1;
	comma = 0;
	while (comma < 3)
	{
		if (!check_color_component(line, &i))
			return (0);
		comma++;
		if (comma < 3)
		{
			if (line[i] != ',')
				return (0);
			i++;
		}
	}
	if (line[i] && line[i] != '\n')
		return (0);
	return (1);
}
