/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_validate_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:35:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 12:00:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	validate_walls(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		if (y == 0 || y == map->height - 1)
		{
			x = 0;
			while (x < map->width)
			{
				if (map->grid[y][x] == '0' || map->grid[y][x] == ' ')
					return (1);
				x++;
			}
		}
		else
		{
			if (map->grid[y][0] == '0' || map->grid[y][0] == ' '
				|| map->grid[y][map->width - 1] == '0'
				|| map->grid[y][map->width - 1] == ' ')
				return (1);
		}
		y++;
	}
	return (0);
}
