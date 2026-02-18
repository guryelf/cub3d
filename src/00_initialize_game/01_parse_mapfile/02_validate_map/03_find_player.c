/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_find_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/18 16:00:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	count_players(t_map *map)
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
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int	store_player(t_map *map)
{
	int	x;
	int	y;

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
				return (0);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	find_and_store_player(t_map *map)
{
	int	count;

	count = count_players(map);
	if (count == 0)
		return (print_error(MSG_NO_PLAYER), 1);
	if (count > 1)
		return (print_error(MSG_MULTIPLE_PLAYERS), 1);
	return (store_player(map));
}
