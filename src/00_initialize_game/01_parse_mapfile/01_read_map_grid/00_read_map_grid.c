/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_read_map_grid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 01:20:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 01:20:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (1);
	return (0);
}

int	is_texture_or_color_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strncmp(&line[i], "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (1);
	if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (1);
	return (0);
}

static void	skip_to_map_section(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (is_texture_or_color_line(line) || is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		free(line);
		break ;
	}
}

static int	calculate_map_height(const char *file_path)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	skip_to_map_section(fd);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			free(line);
			break ;
		}
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	read_map_grid(const char *file_path, t_map *map)
{
	int		fd;
	int		ret;

	map->height = calculate_map_height(file_path);
	if (map->height <= 0)
		return (1);
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (1);
	map->width = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	skip_to_map_section(fd);
	ret = process_lines_loop(fd, map);
	close(fd);
	return (ret);
}
