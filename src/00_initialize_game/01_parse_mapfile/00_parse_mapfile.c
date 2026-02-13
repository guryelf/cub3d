/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_parse_mapfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 00:50:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	map->floor.r = 0;
	map->floor.g = 0;
	map->floor.b = 0;
	map->floor.set = 0;
	map->ceil.r = 0;
	map->ceil.g = 0;
	map->ceil.b = 0;
	map->ceil.set = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = 0;
}

int	parse_mapfile(const char *file_path, t_map *map)
{
	init_map(map);
	if (parse_textures(file_path, map) != 0)
	{
		write(2, "Error: Texture parsing failed\n", 30);
		return (1);
	}
	if (parse_map(file_path, map) != 0)
	{
		write(2, "Error: Map parsing failed\n", 26);
		return (1);
	}
	if (check_map(map) != 0)
	{
		write(2, "Error: Map validation failed\n", 29);
		return (1);
	}
	return (0);
}
