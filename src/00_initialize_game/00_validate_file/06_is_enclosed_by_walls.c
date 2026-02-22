/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_validate_map_walls.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 11:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/21 11:07:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_open_cell(t_map *tempmap, int x, int y)
{
	if (y < 0 || y >= tempmap->height)
		return (1);
	if (!tempmap->grid[y] || x < 0)
		return (1);
	if (!tempmap->grid[y][x] || tempmap->grid[y][x] == ' ')
		return (1);
	return (0);
}

static int	has_zero_open_neighbor(t_map *tempmap, int x, int y)
{
	if (is_open_cell(tempmap, x, y - 1))
		return (1);
	if (is_open_cell(tempmap, x, y + 1))
		return (1);
	if (is_open_cell(tempmap, x - 1, y))
		return (1);
	if (is_open_cell(tempmap, x + 1, y))
		return (1);
	return (0);
}

int	is_enclosed_by_walls(t_map *tempmap)
{
	int	x;
	int	y;
	int	row_len;

	y = 0;
	while (y < tempmap->height)
	{
		row_len = (int)ft_strlen(tempmap->grid[y]);
		x = 0;
		while (x < row_len)
		{
			if (tempmap->grid[y][x] == '0'
				|| is_player_char(tempmap->grid[y][x]))
				if (has_zero_open_neighbor(tempmap, x, y))
					return (print_error(MSG_MAP_NOT_ENCLOSED), 1);
			x++;
		}
		y++;
	}
	return (0);
}
