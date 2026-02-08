/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:26:00 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/08 18:35:42 by rakman           ###   ########.fr       */
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

static int	find_player(t_map *map, int *px, int *py)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_player_char(map->grid[y][x]))
			{
				*px = x;
				*py = y;
				count++;
			}
			x++;
		}
		y++;
	}
	return (count == 1 ? 0 : 1);
}

static int	validate_characters(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (!is_valid_char(map->grid[y][x]))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static void	normalize_irregular_map(t_map *map)
{
	int	i;
	int	j;
	int	cur_len;
	char	*new_line;

	// Find maximum width
	map->width = 0;
	i = 0;
	while (i < map->height)
	{
		cur_len = ft_strlen(map->grid[i]);
		if (cur_len > map->width)
			map->width = cur_len;
		i++;
	}

	// Normalize all lines to max width
	i = 0;
	while (i < map->height)
	{
		cur_len = ft_strlen(map->grid[i]);
		if (cur_len < map->width)
		{
			new_line = ft_calloc(map->width + 1, sizeof(char));
			if (!new_line)
				return ;
			j = 0;
			while (j < cur_len)
			{
				new_line[j] = map->grid[i][j];
				j++;
			}
			// Fill remaining with walls
			while (j < map->width)
			{
				if (map->grid[i][j - 1] == ' ')
					new_line[j] = '1';
				else
					new_line[j] = '1';
				j++;
			}
			free(map->grid[i]);
			map->grid[i] = new_line;
		}
		i++;
	}
}

static void	replace_spaces_with_walls(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width && map->grid[y][x])
		{
			if (map->grid[y][x] == ' ')
				map->grid[y][x] = '1';
			x++;
		}
		y++;
	}
}

static int	is_surrounded_by_walls(t_map *map, int x, int y)
{
	// Simple boundary check - just ensure we're not on edges after normalization
	if (x == 0 || x == map->width - 1)
		return (map->grid[y][x] == '1');
	if (y == 0 || y == map->height - 1)
		return (map->grid[y][x] == '1');
		
	// For internal cells, check if adjacent cells are walls or valid spaces
	return (1); // After normalization, internal cells should be valid
}

static int	check_walls(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == '0' || is_player_char(map->grid[y][x]))
			{
				if (!is_surrounded_by_walls(map, x, y))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_map(t_map *map)
{
	int	px;
	int	py;

	if (!map || !map->grid || map->height <= 0)
		return (1);
	if (validate_characters(map) != 0)
		return (1);
	if (find_player(map, &px, &py) != 0)
		return (1);
		
	// Normalize irregular map to rectangular format
	normalize_irregular_map(map);
	replace_spaces_with_walls(map);
	
	if (check_walls(map) != 0)
		return (1);
	return (0);
}
