/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_has_double_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:56:02 by rakman            #+#    #+#             */
/*   Updated: 2026/02/22 23:16:26 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_fill_all(t_map *tempmap, int x, int y)
{
	if (x < 0 || x >= tempmap->width || y < 0 || y >= tempmap->height)
		return ;
	if (tempmap->grid[y][x] == 'V' || tempmap->grid[y][x] == ' '
		|| tempmap->grid[y][x] == '\n')
		return ;
	tempmap->grid[y][x] = 'V';
	flood_fill_all(tempmap, x + 1, y);
	flood_fill_all(tempmap, x - 1, y);
	flood_fill_all(tempmap, x, y + 1);
	flood_fill_all(tempmap, x, y - 1);
}

int	has_double_map(t_map *tempmap)
{
	int	x;
	int	y;

	flood_fill_all(tempmap, tempmap->player_x, tempmap->player_y);
	y = 0;
	while (y < tempmap->height)
	{
		x = 0;
		while (x < tempmap->width)
		{
			if (tempmap->grid[y][x] != 'V' && tempmap->grid[y][x] != ' '
				&& tempmap->grid[y][x] != '\n' && tempmap->grid[y][x] != '\0')
				return (print_error(MSG_DOUBLE_MAP), 1);
			x++;
		}
		y++;
	}
	return (0);
}
