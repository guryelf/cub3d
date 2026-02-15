/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_dispatch_sneaky_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 02:22:55 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 09:54:40 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int	check_config_section(int fd)
{
	char	*line;
	int		found_count;

	found_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_blank_line(line))
		{
			if (!is_valid_identifier(line) || !validate_line_format(line))
			{
				free(line);
				return (-1);
			}
			found_count++;
			if (found_count == 6)
			{
				free(line);
				return (0);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	return (-1);
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
			map_started = 1;
		else if (map_started)
		{
			free(line);
			consume_remaining_lines(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	dispatch_sneaky_files(const char *file_path)
{
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	if (check_config_section(fd) != 0)
	{
		consume_remaining_lines(fd);
		close(fd);
		return (print_error(MSG_SNEAKY_FILE), 1);
	}
	if (check_map_section(fd) != 0)
	{
		close(fd);
		return (print_error(MSG_SNEAKY_FILE), 1);
	}
	close(fd);
	return (0);
}
