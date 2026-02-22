/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_map_grid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:31:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/22 23:27:33 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	locate_player(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (ft_strchr("NSEW", map->grid[y][x]))
			{
				map->player_x = x;
				map->player_y = y;
				map->player_dir = map->grid[y][x];
				map->grid[y][x] = '0';
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	parse_map_grid(char **raw_grid, t_map *map)
{
	int	y;

	if (!raw_grid)
		return (1);
	y = 0;
	while (raw_grid[y])
		y++;
	map->height = y;
	map->width = (int)ft_strlen(raw_grid[0]);
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (1);
	y = -1;
	while (++y < map->height)
	{
		map->grid[y] = ft_strdup(raw_grid[y]);
		if (!map->grid[y])
			return (1);
	}
	return (locate_player(map));
}
