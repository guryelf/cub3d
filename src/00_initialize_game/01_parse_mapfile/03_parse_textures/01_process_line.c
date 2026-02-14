/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_process_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:40:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 19:40:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	get_texture_type(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (2);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (3);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (4);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (5);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (6);
	return (0);
}

int	process_line(char *line, t_map *map)
{
	int	type;

	type = get_texture_type(line);
	if (type == 0)
		return (0);
	if (type == 1)
		return (set_texture_path(&map->no_path, line, 3));
	if (type == 2)
		return (set_texture_path(&map->so_path, line, 3));
	if (type == 3)
		return (set_texture_path(&map->we_path, line, 3));
	if (type == 4)
		return (set_texture_path(&map->ea_path, line, 3));
	if (type == 5)
		return (parse_color_values(line + 2, &map->floor));
	return (parse_color_values(line + 2, &map->ceil));
}

