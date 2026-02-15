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

#include "../../inc/cub3d.h"

char	*parse_map_line(char *line)
{
	char	*result;
	int		len;
	int		i;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
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

static int	process_single_map_line(char *line, t_map *map, int i)
{
	int	len;

	map->grid[i] = parse_map_line(line);
	if (!map->grid[i])
		return (1);
	len = ft_strlen(map->grid[i]);
	if (len > map->width)
		map->width = len;
	return (0);
}

int	process_lines_loop(int fd, t_map *map, char *first_line)
{
	char	*line;
	int		i;

	i = 0;
	line = first_line;
	while (line)
	{
		if (process_single_map_line(line, map, i) != 0)
			return (free(line), 1);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (0);
}
