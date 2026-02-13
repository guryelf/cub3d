/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:01:22 by rakman            #+#    #+#             */
/*   Updated: 2026/02/13 22:07:43 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != '\t' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

static void	process_count_line(char *line, int *count, int *in_map, int *done)
{
	if (is_map_line(line))
	{
		*in_map = 1;
		(*count)++;
	}
	else if (*in_map && *line != '\n')
		*done = 1;
}

static int	count_map_lines(const char *file_path)
{
	int		fd;
	char	*line;
	int		count;
	int		in_map;
	int		done;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	in_map = 0;
	done = 0;
	line = get_next_line(fd);
	while (line && !done)
	{
		process_count_line(line, &count, &in_map, &done);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (count);
}

int	parse_map(const char *file_path, t_map *map)
{
	map->height = count_map_lines(file_path);
	if (map->height <= 0)
		return (1);
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (1);
	map->width = 0;
	if (read_map_grid(file_path, map) != 0)
		return (1);
	return (0);
}
