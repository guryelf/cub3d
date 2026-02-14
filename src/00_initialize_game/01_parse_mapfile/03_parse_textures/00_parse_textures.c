/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_parse_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:24 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 17:40:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	validate_textures_complete(t_map *map, int err)
{
	if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path
		|| !map->floor.set || !map->ceil.set)
	{
		if (!err)
			print_texture_error(TEX_ERR_MISSING_ELEMENT);
		return (1);
	}
	return (0);
}

int	parse_textures(const char *file_path, t_map *map)
{
	int		fd;
	char	*line;
	int		err;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	err = 0;
	line = get_next_line(fd);
	while (line && !err)
	{
		err = process_line(line, map);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	if (err)
		print_texture_error(err);
	if (validate_textures_complete(map, err))
		return (1);
	return (err != 0);
}
