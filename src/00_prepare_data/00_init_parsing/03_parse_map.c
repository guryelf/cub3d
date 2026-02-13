/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:25:00 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/08 18:25:00 by fguryel          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "map.h"
#include <fcntl.h>

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	

	if (!line[i] || line[i] == '\n')
		return (0);
		

	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && 
			line[i] != '\t' && line[i] != 'N' && line[i] != 'S' && 
			line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

static int	count_map_lines(const char *file_path)
{
	int		fd;
	char	*line;
	int		count;
	int		in_map;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	in_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
		{
			in_map = 1;
			count++;
		}
		else if (in_map && *line != '\n')
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (count);
}

static char	*parse_map_line(char *line)
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

static int	read_map_grid(const char *file_path, t_map *map)
{
	int		fd;
	char	*line;
	int		i;
	int		in_map;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	i = 0;
	in_map = 0;
	line = get_next_line(fd);
	while (line && i < map->height)
	{
		if (is_map_line(line))
		{
			in_map = 1;
			map->grid[i] = parse_map_line(line);
			if (!map->grid[i])
			{
				free(line);
				close(fd);
				return (1);
			}
			if ((int)ft_strlen(map->grid[i]) > map->width)
				map->width = ft_strlen(map->grid[i]);
			i++;
		}
		else if (in_map)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (0);
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
