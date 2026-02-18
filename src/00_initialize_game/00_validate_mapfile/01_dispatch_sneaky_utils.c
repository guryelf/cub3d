/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_dispatch_sneaky_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 04:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/18 16:00:00 by rakman           ###   ########.fr       */
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

static int	count_words(const char *line)
{
	int	i;
	int	word_count;

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
	return (word_count);
}

int	validate_line_format(const char *line)
{
	if (line[0] == 'C' || line[0] == 'F')
		return (validate_color_format(line));
	if (count_words(line) != 2)
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
