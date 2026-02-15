/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_check_zeros_enclosure.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:30:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 03:46:28 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	check_neighbor(t_map *map, int x, int y)
{
	char	c;

	if (y < 0 || y >= map->height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(map->grid[y]))
		return (0);
	c = map->grid[y][x];
	if (c == ' ' || c == '\0')
		return (0);
	return (1);
}

int	check_zeros_enclosure(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == '0')
			{
				if (check_neighbor(map, x, y - 1) == 0)
					return (1);
				if (check_neighbor(map, x, y + 1) == 0)
					return (1);
				if (check_neighbor(map, x - 1, y) == 0)
					return (1);
				if (check_neighbor(map, x + 1, y) == 0)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
