/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_dispatch_sneaky_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 02:22:55 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 04:28:11 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int	process_config_line(char *line, int *found_count)
{
	if (!is_blank_line(line))
	{
		if (is_valid_identifier(line) && validate_line_format(line))
			(*found_count)++;
		else
			return (-1);
		if (*found_count == 6)
			return (1);
	}
	return (0);
}

static int	check_config_section(int fd)
{
	char	*line;
	int		found_count;
	int		status;

	found_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		status = process_config_line(line, &found_count);
		if (status == -1)
		{
			free(line);
			return (-1);
		}
		if (status == 1)
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (-1);
}

static int	handle_map_blank_line(int fd, char *line)
{
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
	return (1);
}

static int	check_map_section(int fd)
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_blank_line(line))
		{
			map_started = 1;
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (map_started && is_blank_line(line))
			return (handle_map_blank_line(fd, line));
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	dispatch_sneaky_files(const char *file_path)
{
	int		fd;
	int		result;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	if (check_config_section(fd) != 0)
	{
		consume_remaining_lines(fd);
		close(fd);
		write(2, "Error\nInvalid configuration section\n", 37);
		return (1);
	}
	result = check_map_section(fd);
	close(fd);
	if (result != 0)
	{
		write(2, "Error\nInvalid map section\n", 26);
		return (1);
	}
	return (0);
}
