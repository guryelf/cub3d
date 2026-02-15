/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_validate_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:40:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/13 22:07:43 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player_char(c));
}

static int	validate_characters(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y] && map->grid[y][x])
		{
			if (!is_valid_char(map->grid[y][x]))
				return (print_error(MSG_INVALID_MAP_CHAR), 1);
			x++;
		}
		y++;
	}
	return (0);
}

static int	find_and_store_player(t_map *map)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y] && map->grid[y][x])
		{
			if (is_player_char(map->grid[y][x]))
			{
				map->player_x = x;
				map->player_y = y;
				map->player_dir = map->grid[y][x];
				map->grid[y][x] = '0';
				count++;
			}
			x++;
		}
		y++;
	}
	if (count == 0)
		return (print_error(MSG_NO_PLAYER), 1);
	if (count > 1)
		return (print_error(MSG_MULTIPLE_PLAYERS), 1);
	return (0);
}

int	validate_map(t_map *map)
{
	if (!map || !map->grid || map->height <= 0)
		return (1);
	if (validate_characters(map) != 0)
		return (1);
	if (find_and_store_player(map) != 0)
		return (1);
	if (normalize_map_grid(map) != 0)
		return (1);
	if (validate_enclosure(map) != 0)
		return (1);
	return (0);
}
