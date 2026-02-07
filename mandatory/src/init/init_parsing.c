/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:12 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/07 05:18:47 by fguryel          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "map.h"

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
}

int	init_parsing(const char *file_path, t_map *map)
{
	if (parse_file(file_path) != 0)
		return (1);
	init_map(map);
	if (parse_textures(file_path, map) != 0)
		return (1);
	return (0);
}
