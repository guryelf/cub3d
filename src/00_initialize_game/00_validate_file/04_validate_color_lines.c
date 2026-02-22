/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_validate_color_lines.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/22 22:52:09 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	check_rgb_value(const char *line, int *i)
{
	int	digit_count;
	int	val;

	if (!(line[*i] >= '0' && line[*i] <= '9'))
		return (print_error(MSG_INVALID_COLOR), 1);
	val = ft_atoi(line + *i);
	if (val < 0 || val > 255)
		return (print_error(MSG_COLOR_RANGE), 1);
	*i = read_digits(line, *i, &digit_count);
	if (digit_count < 1 || digit_count > 3)
		return (print_error(MSG_INVALID_COLOR), 1);
	return (0);
}

int	is_valid_color_line(const char *line)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (count < 3)
	{
		i = skip_spaces_fc(line, i);
		if (check_rgb_value(line, &i) != 0)
			return (1);
		i = skip_spaces_fc(line, i);
		if (count < 2)
		{
			if (line[i] != ',')
				return (print_error(MSG_INVALID_COLOR), 1);
			i++;
		}
		count++;
	}
	if (line[i] && line[i] != '\n')
		return (print_error(MSG_INVALID_COLOR), 1);
	return (0);
}
