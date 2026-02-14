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

#include "map.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player_char(c));
}

static int	has_space_in_middle(char *line)
{
	int	i;
	int	found_map_char;

	i = 0;
	found_map_char = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || is_player_char(line[i]))
			found_map_char = 1;
		else if (line[i] == ' ' && found_map_char)
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] && (line[i] == '0' || line[i] == '1'
					|| is_player_char(line[i])))
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}

static int	validate_characters(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		if (has_space_in_middle(map->grid[y]))
			return (1);
		x = 0;
		while (map->grid[y] && map->grid[y][x])
		{
			if (!is_valid_char(map->grid[y][x]))
				return (1);
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
	return (count != 1);
}

int	validate_map(t_map *map)
{
	if (!map || !map->grid || map->height <= 0)
		return (1);
	if (validate_characters(map) != 0)
		return (1);
	if (find_and_store_player(map) != 0)
		return (1);
	normalize_map_grid(map);
	if (validate_enclosure(map) != 0)
		return (1);
	return (0);
}
