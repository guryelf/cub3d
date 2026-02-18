/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_file_has_double_map.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:25:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/18 15:57:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static void	flood_fill_dm(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return ;
	if (map->grid[y][x] == 'V' || map->grid[y][x] == ' ')
		return ;
	map->grid[y][x] = 'V';
	flood_fill_dm(map, x + 1, y);
	flood_fill_dm(map, x - 1, y);
	flood_fill_dm(map, x, y + 1);
	flood_fill_dm(map, x, y - 1);
}

static int	find_player_and_fill(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S'
				|| map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
			{
				flood_fill_dm(map, x, y);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

static int	has_unreachable_map_chars(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] != 'V' && map->grid[y][x] != ' ')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static void	free_temp_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	free(map->grid);
}

int	file_has_double_map(const char *file_path)
{
	t_map	map;
	int		result;

	ft_bzero(&map, sizeof(t_map));
	if (read_map_grid(file_path, &map) != 0)
		return (0);
	if (normalize_map_grid(&map) != 0)
		return (free_temp_map(&map), 0);
	if (find_player_and_fill(&map) != 0)
		return (free_temp_map(&map), 0);
	result = has_unreachable_map_chars(&map);
	free_temp_map(&map);
	if (result)
		return (print_error("Map has unreachable sections (double map)"), 1);
	return (0);
}
