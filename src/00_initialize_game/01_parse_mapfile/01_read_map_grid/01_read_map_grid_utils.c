/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_read_map_grid_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:12:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 01:20:00 by rakman           ###   ########.fr       */
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

char	*parse_map_line(char *line)
{
	char	*result;
	int		len;
	int		i;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		len--;
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = line[i];
		i++;
	}
	return (result);
}

int	process_grid_line(char *line, t_map *map, int *i, int *in_map)
{
	int	len;

	if (is_map_line(line))
	{
		*in_map = 1;
		map->grid[*i] = parse_map_line(line);
		if (!map->grid[*i])
			return (1);
		len = ft_strlen(map->grid[*i]);
		if (len > map->width)
			map->width = len;
		(*i)++;
		return (0);
	}
	if (*in_map)
		return (2);
	return (0);
}

int	process_lines_loop(int fd, t_map *map)
{
	char	*line;
	int		i;
	int		in_map;
	int		ret;

	i = 0;
	in_map = 0;
	line = get_next_line(fd);
	while (line && i < map->height)
	{
		ret = process_grid_line(line, map, &i, &in_map);
		if (ret == 1)
		{
			free(line);
			return (1);
		}
		if (ret == 2)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (0);
}
