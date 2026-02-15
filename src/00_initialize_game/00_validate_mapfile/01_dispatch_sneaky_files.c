/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_dispatch_sneaky_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 02:22:55 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 03:30:30 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int	is_blank_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid_identifier(const char *line)
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

static int	validate_line_format(const char *line)
{
	int	i;
	int	word_count;

	if (line[0] == 'C' || line[0] == 'F')
		return (1);
	i = 0;
	word_count = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] && line[i] != '\n')
		{
			word_count++;
			while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
				i++;
		}
	}
	return (word_count == 2);
}

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
			if (is_valid_identifier(line) && validate_line_format(line))
				found_count++;
			else
			{
				free(line);
				return (-1);
			}
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
		{
			map_started = 1;
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (map_started && is_blank_line(line))
		{
			free(line);
			while (line)
			{
				line = get_next_line(fd);
				free(line);
			}
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

/*
** Check if the file's last character is '\n'
** If it is, return error (1), otherwise return success (0)
** This is to prevent sneaky files that have a valid map but end with a newline,
static int	check_file_last_char(const char *file_path)
{
	int		fd;
	char	*line;
	char	*last_line;
	int		len;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	last_line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (last_line)
			free(last_line);
		last_line = line;
		line = get_next_line(fd);
	}
	close(fd);
	if (!last_line)
		return (1);
	len = ft_strlen(last_line);
	if (len > 0 && last_line[len - 1] == '\n')
	{
		free(last_line);
		return (1);
	}
	free(last_line);
	return (0);
}*/

int	dispatch_sneaky_files(const char *file_path)
{
	int		fd;
	int		result;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	if (check_config_section(fd) != 0)
	{
		while (1)
		{
			line = get_next_line(fd);
			if (!line)
				break ;
			free(line);
		}
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