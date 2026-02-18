/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_dispatch_sneaky_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 04:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 11:52:04 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	is_blank_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_identifier(const char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	return (0);
}

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

static int	validate_color_format(const char *line)
{
	int	i;
	int	digit_count;
	int	comma;

	i = 1;
	comma = 0;
	while (comma < 3)
	{
		i = skip_spaces_fc(line, i);
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (0);
		i = read_digits(line, i, &digit_count);
		if (digit_count < 1 || digit_count > 3)
			return (0);
		i = skip_spaces_fc(line, i);
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

int	validate_line_format(const char *line)
{
	int	i;
	int	word_count;

	if (line[0] == 'C' || line[0] == 'F')
		return (validate_color_format(line));
	i = 0;
	word_count = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] && line[i] != '\n')
		{
			word_count++;
			while (line[i] && line[i] != ' ' && line[i] != '\n')
				i++;
		}
	}
	if (word_count != 2)
		return (0);
	return (1);
}

void	consume_remaining_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
