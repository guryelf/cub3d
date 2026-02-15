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

#include "../../inc/cub3d.h"

static int	validate_textures_complete(t_map *map)
{
	if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path
		|| !map->floor.set || !map->ceil.set)
		return (print_error(MSG_MISSING_TEXTURE), 1);
	return (0);
}

static int	process_line(char *line, t_map *map)
{
	while (*line && *line == ' ')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_texture_path(&map->no_path, line));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_texture_path(&map->so_path, line));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_texture_path(&map->we_path, line));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_texture_path(&map->ea_path, line));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color_values(line + 2, &map->floor));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color_values(line + 2, &map->ceil));
	return (0);
}

int	parse_textures(const char *file_path, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		if (process_line(line, map) != 0)
			return (free(line), close(fd), 1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_textures_complete(map));
}
