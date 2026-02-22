/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_validate_map.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:40:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/18 16:00:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	store_player(t_map *tempmap, int x, int y, int *player_count)
{
	tempmap->player_x = x;
	tempmap->player_y = y;
	(*player_count)++;
}

static int	validate_characters(t_map *tempmap)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = -1;
	while (++y < tempmap->height)
	{
		x = -1;
		while (tempmap->grid[y] && tempmap->grid[y][++x])
		{
			if (is_player_char(tempmap->grid[y][x]))
				store_player(tempmap, x, y, &player_count);
			else if (!is_valid_char(tempmap->grid[y][x]))
				return (print_error(MSG_INVALID_MAP_CHAR), 1);
		}
	}
	if (player_count == 0)
		return (print_error(MSG_NO_PLAYER), 1);
	if (player_count > 1)
		return (print_error(MSG_MULTIPLE_PLAYERS), 1);
	return (0);
}

static int	populate_tempmap(t_rawdata *rawdata, t_map *tempmap)
{
	int	y;

	ft_bzero(tempmap, sizeof(t_map));
	if (!rawdata->grid)
		return (1);
	y = 0;
	while (rawdata->grid[y])
		y++;
	tempmap->height = y;
	tempmap->grid = ft_calloc(tempmap->height + 1, sizeof(char *));
	if (!tempmap->grid)
		return (1);
	y = -1;
	while (++y < tempmap->height)
	{
		tempmap->grid[y] = ft_strdup(rawdata->grid[y]);
		if (!tempmap->grid[y])
			return (free_map_data(tempmap), 1);
	}
	return (0);
}

int	validate_map_grid(t_rawdata *rawdata)
{
	t_map	tempmap;

	if (populate_tempmap(rawdata, &tempmap) != 0)
		return (1);
	if (validate_characters(&tempmap) != 0)
		return (free_map_data(&tempmap), 1);
	if (normalize_map_grid(tempmap.grid) != 0)
		return (free_map_data(&tempmap), 1);
	tempmap.width = 0;
	if (tempmap.grid && tempmap.grid[0])
		tempmap.width = ft_strlen(tempmap.grid[0]);
	if (is_enclosed_by_walls(&tempmap) != 0)
		return (free_map_data(&tempmap), 1);
	if (has_double_map(&tempmap) != 0)
		return (free_map_data(&tempmap), 1);
	free_map_data(&tempmap);
	return (0);
}
